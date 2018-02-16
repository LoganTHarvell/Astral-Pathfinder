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


// MARK: - Initialization Methods

void Planet::initHomeworld() {
  using namespace PlanetParameters;
  // initializes random planet
  initPlanet();
  
  // Sets homeword resources
  fertility = startPopulation/foodRqmt;
  deposits = (shipCost*2) + 50;
  
  // Sets homeworld status
  status = colonized;
}

void Planet::initPlanet() {
  using namespace PlanetParameters;
  
  // Set planet coordinates
  position.x = rand()%PlanetManagerParameters::numberOfPlanets;
  position.y = rand()%PlanetManagerParameters::numberOfPlanets;
  
  size = { planetTexSize, planetTexSize };
  texture = TextureManager::loadTexture("Resources/Assets/planet.png");
  
  // Sets planet fertility to random value
  fertility = (rand()%(fertilityRange+1) + minFertility);
  
  // Sets planet deposits to random value
  deposits = (rand()%(depositsRange+1)) + minDeposits;
  
  // Sets planet status
  status = undiscovered;
}


// MARK: - Game Loop Methods

void Planet::update() {
  SDL_Point pos = uiPosition();
  rect.x = pos.x;
  rect.y = pos.y;
  
  rect.w = size.w;
  rect.h = size.h;
}

void Planet::render() {
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

// MARK: - Helper Methods

SDL_Point Planet::uiPosition() {
  return Map::uiPosition(position);
}
