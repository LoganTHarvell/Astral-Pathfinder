//
//  Planet.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Planet.hpp"

// MARK: Source Files
#include "Game.hpp"
#include "PlanetManager.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Ship.hpp"


// MARK: - Initialization Methods

void Planet::initHomeworld() {
  using namespace PlanetParameters;
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

  infrastructure = 5000;
  food = homeStartFertility;
  
  // Initial birth and death rate multiplier
  birthMult = (rand()/(RAND_MAX/birthMultiplierRange)) + minBirthMultiplier;
  deathMult = (rand()/(RAND_MAX/deathMultiplerRange)) + minDeathMultiplier;
  
  // Initial births and deaths in first growth period
  births = population * birthMult;
  deaths = population * deathMult;
  
  // Sets homeworld status
  status = colonized;
  playerDocked = true;
  
  SDL_SetTextureAlphaMod(texture, 255);
}

void Planet::initPlanet() {
  using namespace PlanetParameters;
  
  // Set planet coordinates
  coordinates.x = rand()%PlanetManagerParameters::numberOfPlanets;
  coordinates.y = rand()%PlanetManagerParameters::numberOfPlanets;
  
  // Set planet rect
  SDL_Point tmp = uiPosition(coordinates);
  rect.x = tmp.x;
  rect.y = tmp.y;
  rect.w = planetTexSize;
  rect.h = planetTexSize;
  
  texture = TextureManager::loadTexture(planetTextureFile);
  collider = new ColliderComponent(rect);
  
  population = 0;
  
  // Sets planet fertility to random value
  fertility = (rand()%(fertilityRange+1) + minFertility);
  // Sets planet deposits to random value
  deposits = (rand()%(depositsRange+1)) + minDeposits;
  
  infraPercent = startInfraPercent;
  reservePercent = startReservePercent;
  farmingPercent = startFarmingPercent;
  miningPercent = startMiningPercent;
  
   minerals = infrastructure = food = 0;
  
  // Initial birth and death rate multiplier
  birthMult = 0;
  deathMult = 0;
  
  // Initial births and deaths in first growth period
  births = 0;
  deaths = 0;
  
  // Set flags
  isOverproducing = false;
  markedOverProd = false;
  overproductionStartTime = 0;
  
  playerDocked = alienDocked = false;
  
  // Sets planet status
  status = undiscovered;
  SDL_SetTextureAlphaMod(texture, 127);
}


// MARK: - Game Loop Methods

void Planet::update(Game::State *gs) {
  updateStatus();
  updatePopulation(gs->frame);
  updateMining();
  updateFarming();
}

void Planet::render(Game::State *gs) {
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

// MARK: - Planet Methods

void Planet::clicked() {
  SDL_SetTextureColorMod(texture, 0, 255, 0);
}

void Planet::revertClick() {
  SDL_SetTextureColorMod(texture, 255, 255, 255);
}

void Planet::toggleDockedShip(int tag) {
  using namespace ShipParameters;
  
  switch (tag) {
    case ShipType::playerShip:
      playerDocked = !playerDocked;
      population += playerDocked ? shipPopulation : -(shipPopulation);
      break;
    case ShipType::alienWarship:
      alienDocked = !alienDocked;
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

// MARK: - Helper Methods

void Planet::updateStatus() {
  if (status == undiscovered && playerDocked) {
    status = discovered;
    SDL_SetTextureAlphaMod(texture, 255);
  }
  else if (status == discovered && (population > 0 || playerDocked)) {
    status = colonized;
  }
  else if (status == colonized && (population == 0 && !playerDocked)) {
    status = discovered;
  }
}

void Planet::updatePopulation(Uint32 frame) {
  using namespace PlanetParameters;
  
  // If no people to populate, return immediately
  if (population <= 0 && !playerDocked) return;
  
  // Calculates surplus food produced
  int surplus = food-(population*foodRqmt);
  if (0 > surplus) surplus = 0;
  
  if (frame%growthPeriod == 0) {
    birthMult = (rand()/(RAND_MAX/birthMultiplierRange)) + minBirthMultiplier;
    deathMult = (rand()/(RAND_MAX/deathMultiplerRange)) + minDeathMultiplier;
    births = (population) * (birthMult+(surplus/(population*foodRqmt)));
    deaths = population * deathMult;
  }
  
  population += (births/static_cast<float>(growthPeriod));
  population -= (deaths/static_cast<float>(growthPeriod));
  
  // Calculates deaths due to starvation
  int fedPopulation = (food/foodRqmt);
  if (population > (fedPopulation)) {
    population -= (population-fedPopulation)/static_cast<float>(growthPeriod);
  }
  
  // Calculates deaths due to infrastructure limitations
  if (population > infrastructure) {
    population -= (population-infrastructure);
  }
  
  // Guards against ship crew "dying"
  if (playerDocked && population < ShipParameters::shipPopulation) {
    population = ShipParameters::shipPopulation;
  }
  // Guards against negative population values
  else if (population < 0) {
    population = 0;
  }
}

void Planet::updateMining() {
  using PlanetParameters::miningRate;
  
  // If there is no one or nothing to mine, then return right away
  if (population <= 0 || deposits <= 0) return;
  
  // Calculates amount of population dedicated to mining
  int workers = population;
  workers *= (miningPercent/100.0f);
  
  float product = workers*miningRate;
  
  if (product < 0 ) return;
  
  if (product <= deposits) {
    minerals += product;
    deposits -= product;
  }
  else {
    minerals += deposits;
    deposits = 0;
  }
}

void Planet::updateFarming() {
  using namespace PlanetParameters;
  
  food = 0; // Resets food
  
  // If there is no one or nothing to farm, then return right away
  if (population <= 0 || fertility <= 0) return;
  
  // Calculates amount of population dedicated to farming
  int workers = population;
  workers *= (farmingPercent/100.0f);
  
  float product = workers*farmingRate;  // Food produced
  
  // Return if no food produced
  if (product < 0 ) {
    if (isOverproducing) isOverproducing = markedOverProd = false;
    return;
  }
  
  // If food produced is less than max fertility, return produced amount
  if (product < fertility+1) {
    food = product;
    if (isOverproducing) isOverproducing = markedOverProd = false;
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
    
    // Mark visually with color mod when overproducing, flag as marked
    if (isOverproducing && !markedOverProd) {
      SDL_SetTextureColorMod(texture, 200, 0, 0);
      markedOverProd = true;
    }
  }
}

SDL_Point Planet::uiPosition(SDL_Point p) {
  return Map::uiPosition(p);
}
