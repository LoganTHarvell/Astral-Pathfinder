//
//  Planet.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  A GameObject class extension for modeling the Planet game element. Contains
//  and manages an individual planet's state and resources. Planet state
//  includes ship-docking using collision information from collider componenet.
//  Resources update according to a growth period cycle system over many frames.
//  Also handles initializing, updating, and rendering.

// MARK: Header File
#include "Planet.hpp"

// MARK: Libraries and Frameworks
#include "TextureManager.hpp"

// MARK: Source Files
#include "PlanetManager.hpp"
#include "PlayerShip.hpp"
#include "Map.hpp"


// MARK: - Initialization Methods

void Planet::initHomeworld() {
  using namespace Parameters::Planet;
  // initializes random planet
  initPlanet();
  
  // Sets homeworld resources
  population = homeStartPopulation;
  fertility = homeStartFertility;
  deposits = homeStartDeposits;
  
  // Sets homeworld to reserve all minerals mined
  miningPercent = homeStartMiningPercent;
  farmingPercent = homeStartFarmingPercent;
  infraPercent = homeStartInfraPercent;
  reservePercent = homeStartReservePercent;

  infrastructure = homeStartPopulation;
  food = homeStartFertility;
  
  // Initial birth and death rate multiplier
  birthMult = (rand()/(RAND_MAX/birthMultiplierRange)) + minBirthMultiplier;
  deathMult = (rand()/(RAND_MAX/deathMultiplierRange)) + minDeathMultiplier;
  
  // Initial births and deaths in first growth period
  births = population * birthMult;
  deaths = population * deathMult;
  growthRate = (births - deaths)/static_cast<float>(growthPeriod);
  
  // Sets homeworld status
  status = colonized;
  playerDocked = true;
  populationCheck = homeStartPopulation;
}

void Planet::initPlanet() {
  using namespace Parameters::Planet;
  
  // Set planet coordinates
  coordinates.x = rand()%Parameters::PlanetManager::numberOfPlanets;
  coordinates.y = rand()%Parameters::PlanetManager::numberOfPlanets;
  
  // Set planet rect
  SDL_Point tmp = uiPosition(coordinates);
  rect.x = tmp.x;
  rect.y = tmp.y;
  rect.w = planetTexSize;
  rect.h = planetTexSize;
  
  outlineRect.x = rect.x-(planetOutlineSize-rect.w)/2;
  outlineRect.y = rect.y-(planetOutlineSize-rect.h)/2;
  outlineRect.w = planetOutlineSize;
  outlineRect.h = planetOutlineSize;
  
  TextureManager::loadTexture(planetTextureFile, &texture, Game::renderer);
  TextureManager::loadTexture(planetOutlineFile, &outlineTexture, Game::renderer);
  
  collider = new ColliderComponent(rect);
  eventManager = new EventsComponent(mapPosition());
  
  population = 0;
  
  // Sets planet fertility to random value
  fertility = (rand()%(fertilityRange+1) + minFertility);
  
  // Sets planet deposits to random value
  deposits = (rand()%(depositsRange+1)) + minDeposits;
  
  miningPercent = startMiningPercent;
  farmingPercent = startFarmingPercent;
  infraPercent = startInfraPercent;
  reservePercent = startReservePercent;
  
  minerals = infrastructure = food = 0;
  
  // Initial birth and death rate multiplier
  birthMult = 0;
  deathMult = 0;
  
  // Initial births and deaths in first growth period
  births = 0;
  deaths = 0;
  growthRate = 0;
  
  // Set flags
  isOverproducing = false;
  overproductionStartTime = 0;

  playerDocked = alienDocked = false;
  frameDocked = 0;
  selected = false;

  populationDec = false;
  populationCheck = 0;
  
  // Sets planet status
  status = undiscovered;
  
  events.plague = false;
  events.blight = false;
  events.mineCollapse = false;
}


// MARK: - Game Loop Methods

void Planet::update(Game::State *gs) {
  updateStatus();
  updateRandomEvents(gs->frame);
  updatePopulation(gs->frame);
  updateMining();
  updateFarming();
  updateEventComponent();
  updateColors();
}

void Planet::render(Game::State *gs) {
  renderEvents();
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

// MARK: - Planet Methods

void Planet::clicked() {
  selected = true;
}

void Planet::revertClick() {
  selected = false;
}

void Planet::toggleDockedShip(int tag, Uint32 frame) {
  using namespace Parameters::Planet;
  using ShipType = Ship::ShipType;
  
  switch (tag) {
    case ShipType::playerShip:
      playerDocked = !playerDocked;
      if (playerDocked && frameDocked + growthPeriod < frame) {
        frameDocked = frame;
      }
      break;
    case ShipType::alienWarship:
      alienDocked = !alienDocked;
      if (alienDocked) {
        if (minerals > 0) minerals = 0;
        if (population > 0
            && alienInvasionRate > rand()/static_cast<float>(RAND_MAX)) {
          population = 0;
        }
      }
      break;
      
    default:
      break;
  }
}

int Planet::makeFuel(int amount) {
  if (amount <= 0) return 0;
  
  if (amount <= minerals) {
    minerals -= amount;
    return amount;
  }
  else {
    amount = minerals;
    minerals = 0;
    return amount;
  }
}

SDL_Point Planet::mapPosition() {
  return Map::mapPosition(getCenter());
}


// MARK: - Helper Methods

void Planet::updateStatus() {
  if (status == undiscovered && playerDocked)
    status = discovered;
  else if (status == discovered && population > 0)
    status = colonized;
  else if (status == colonized && population == 0)
    status = discovered;
}

void Planet::updateRandomEvents(Uint32 frame) {
  using namespace Parameters::Planet;
  
  // Exits immediately if planet has no population
  if (population <= 0) return;
  
  // Updates random event flags for growth period
  if ((frame-frameDocked)%growthPeriod == 0) {
    float randMax = static_cast<float>(RAND_MAX);

    events.plague = (plagueRate > rand()/randMax);
    
    if (fertility > 0) {
      events.blight = (blightRate > rand()/randMax);
    }
    else events.blight = false;
    
    if (deposits > 0) {
      events.mineCollapse = (mineCollapseRate > rand()/randMax);
    }
    else events.mineCollapse = false;
    
  }
}

void Planet::updatePopulation(Uint32 frame) {
  using namespace Parameters::Planet;
  
  // Adjusts working population
  int workingPop = this->population;
  workingPop += playerDocked ? 1000 : 0;
  
  // If no people to populate, return immediately
  if (workingPop <= 0) return;
  
  // Calculates surplus food percentage
  float foodNeeded = population*foodRqmt;
  float surplus = food-foodNeeded;
  if (population > 0 && surplus > 0) surplus = (surplus/foodNeeded)*0.1;
  else surplus = 0;
  
  // Resets births and deaths rates for growth period
  if ((frame-frameDocked)%growthPeriod == 0) {
    populationDec = (population < populationCheck) ? true : false;
    populationCheck = population;
    
    birthMult = (rand()/(RAND_MAX/birthMultiplierRange)) + minBirthMultiplier;
    
    if (events.plague)
      deathMult = plagueMultiplier;
    else
      deathMult = (rand()/(RAND_MAX/deathMultiplierRange)) + minDeathMultiplier;
    
    births = (workingPop) * (birthMult+surplus);
    deaths = workingPop * deathMult;

    growthRate = (births - deaths)/static_cast<float>(growthPeriod);
  }
  
  // Updates population with growth rate (people per frame)
  population += growthRate;
  
  // Calculates deaths due to starvation, prevents growth with no food
  int fedPopulation = (food/foodRqmt);
  if (fedPopulation <= 0 && growthRate > 0) {
    population -= growthRate;
  }
  else if (population > (fedPopulation)) {
    population -= (population-fedPopulation)*starveRate;
  }
  
  // Limits population to infrastructure limits
  if (population > infrastructure) {
    population = infrastructure;
  }
  
  // Guards against negative population values
  if (population < 0) {
    population = 0;
  }
}

void Planet::updateMining() {
  using namespace Parameters::Planet;
  
  // Adjusts working population
  int workingPop = this->population;
  workingPop += playerDocked ? 1000 : 0;
  
  // If there is no one or nothing to mine, then return right away
  if (workingPop <= 0 || deposits <= 0) return;
  
  // Calculates amount of population dedicated to mining
  int miners = workingPop * (miningPercent/100.0f);
  
  float rate = miningRate;
  if (events.mineCollapse) rate *= mineCollapseMultiplier;
  
  float product = miners*rate;
  if (product < 0 ) return;
  
  if (product <= deposits) {
    minerals += (product * (reservePercent/100.0f));
    infrastructure += (product * (infraPercent/100.0f)) * infrastructureCost;
    deposits -= product;
  }
  else {
    minerals += deposits;
    deposits = 0;
  }
}

void Planet::updateFarming() {
  using namespace Parameters::Planet;
  
  food = 0; // Resets food
  
  // Adjusts working population
  int workingPop = this->population;
  workingPop += playerDocked ? 1000 : 0;
  
  // If there is no one or nothing to farm, then return right away
  if (workingPop <= 0 || fertility <= 0) return;
  
  // Calculates amount of population dedicated to farming
  int farmers = workingPop * (farmingPercent/100.0f);
  
  float rate = farmingRate;
  if (events.blight) {
    rate *= blightMultiplier;
  }
  
  float product = farmers*rate;  // Food produced
  
  // Return if no food produced
  if (product < 0 ) {
    if (isOverproducing) isOverproducing = false;
    return;
  }
  
  // If food produced is less than max fertility, return produced amount
  if (product < fertility+1) {
    food = product;
    if (isOverproducing) isOverproducing = false;
  }
  // Else food is overproduced
  else {
    // Reduced production after exceeding max fertility
    food = fertility + (sqrt(product-fertility));
    
    // Flag overproduction and start time
    if (isOverproducing == false) {
      overproductionStartTime = SDL_GetTicks();
      isOverproducing = true;
    }

    // Calculate time overproducing, decay fertility after delay
    Uint32 overprodTime = (SDL_GetTicks()-overproductionStartTime)/1000;
    if (overprodTime >= fertDecayDelay) {
      fertility -= sqrt(food-fertility) * fertDecay * overprodTime;
      if (fertility < 0) fertility = 0;
    }
  }
}

void Planet::updateEventComponent() {
  eventManager->update(events.blight, events.plague, events.mineCollapse, populationDec, isOverproducing);
}

// Updates a planet color code based on status
void Planet::updateColors() {
  using namespace Parameters::Planet;

  if (status == undiscovered) {
    SDL_SetTextureAlphaMod(texture, undiscColor.a);
    SDL_SetTextureColorMod(texture,
                           undiscColor.r, undiscColor.g, undiscColor.b);
    return;
  }
  
  // Resets alpha value
  SDL_SetTextureAlphaMod(texture, normalAlpha);
  
  if (selected) {
    SDL_SetTextureColorMod(texture,
                           selectedColor.r, selectedColor.g, selectedColor.b);
    return;
  }
  
  if (status == discovered) {
    SDL_SetTextureColorMod(texture,
                           discoverColor.r, discoverColor.g, discoverColor.b);
    return;
  }
  
  // Colony related color codes
  if (populationDec) {
    SDL_SetTextureColorMod(texture,
                           popDecColor.r, popDecColor.g, popDecColor.b);
  }
  else if (isOverproducing) {
    SDL_SetTextureColorMod(texture,
                           overprodColor.r, overprodColor.g, overprodColor.b);
  }
  else {
    SDL_SetTextureAlphaMod(texture, colonyColor.a);
    SDL_SetTextureColorMod(texture,
                           colonyColor.r, colonyColor.g, colonyColor.b);
  }
}

SDL_Point Planet::uiPosition(SDL_Point p) {
  return Map::uiPosition(p);
}

void Planet::renderEvents() {
  if (events.blight || events.plague || events.mineCollapse)
    SDL_RenderCopy(Game::renderer, outlineTexture, NULL, &outlineRect);
}
