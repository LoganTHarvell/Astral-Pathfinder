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
  
  // Sets homeword resources
  population = startPopulation;
  deposits = (shipCost*2) + 50;
  fertility = population/foodRqmt;
  food = population*foodRqmt;
  
  // Sets homeworld status
  status = colonized;
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
  
  depositsPercent = fertilityPercent = infraPercent = reservePercent = 50;
  minerals = food = 0;
  
  playerDocked = alienDocked = false;
  
  // Sets planet status
  status = undiscovered;
}


// MARK: - Game Loop Methods

void Planet::update() {
  updateStatus();
}

void Planet::render() {
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

// MARK: - Helper Methods

void Planet::updateStatus() {
  if (status == undiscovered && playerDocked) status = discovered;
  if (status == discovered && population > 0) status = colonized;
  if (status == colonized && population == 0) status = discovered;
}

SDL_Point Planet::uiPosition(SDL_Point p) {
  return Map::uiPosition(p);
}
