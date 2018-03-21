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
  population = startPopulation;
  fertility = population*foodRqmt;
  deposits = fuelCost;
  
  // Sets homeworld to reserve all minerals mined
  miningPercent = homeStartMiningPercent;
  farmingPercent = homeStartFarmingPercent;
  infraPercent = homeStartInfraPercent;
  reservePercent = homeStartReservePercent;
  
  food = (population*(farmingPercent/100.0f))*farmingCost;
  
  // Sets homeworld status
  status = colonized;
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
  
  minerals = food = 0;
  
  playerDocked = alienDocked = false;
  
  // Sets planet status
  status = undiscovered;
  SDL_SetTextureAlphaMod(texture, 127);
}


// MARK: - Game Loop Methods

void Planet::update(Game::State *gs) {
  updateStatus();
  
  if (deposits > 0) updateMining();
  if (fertility > 0) updateFarming();
  
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
  using ShipType = ShipParameters::ShipType;
  
  switch (tag) {
    case ShipType::playerShip:
      playerDocked = !playerDocked;
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

void Planet::updateMining() {
  using PlanetParameters::miningCost;
  
  // If there is no one to farm, then return right away
  if (population <= 0 && !playerDocked) return;
  
  int workers = population;
  if (playerDocked) workers += ShipParameters::shipPopulation;
  workers *= (miningPercent/100.0f);
  
  float product = workers*miningCost;
  
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
  using PlanetParameters::farmingCost;
  
  // If there is no one to farm, then return right away
  if (population <= 0 && !playerDocked) return;
  
  int workers = population;
  if (playerDocked) workers += ShipParameters::shipPopulation;
  workers *= (farmingPercent/100.0f);
  
  float product = workers*farmingCost;
  
  if (product < 0 ) return;
  
  if (product <= fertility) {
    food = product;
  }
  else {
    food = product;
    fertility -= (product-fertility);
    if (fertility < 0) fertility = 0;
    
    SDL_SetTextureColorMod(texture, 128, 0, 0);
  }
}

SDL_Point Planet::uiPosition(SDL_Point p) {
  return Map::uiPosition(p);
}
