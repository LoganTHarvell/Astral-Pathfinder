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
#include "parameters.h"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"


// MARK: - Planet Constants

const int Planet::planetTexSize = 8;


// MARK: - Initialization Methods

void Planet::initHomeworld() {
  // initializes random planet
  initPlanet();
  
  // Sets homeword resources
  fertility = STARTING_POPULATION/PEOPLE_FOOD_RQMT;
  deposits = SHIP_COST * 2 + 50;
  
  // Sets homeworld status
  status = colonized;
}

void Planet::initPlanet() {
  // Set planet coordinates
  position.x = rand()%NUMBER_OF_PLANETS;
  position.y = rand()%NUMBER_OF_PLANETS;
  
  size = { planetTexSize, planetTexSize };
  texture = TextureManager::loadTexture("Resources/Assets/planet.png");
  
  // Sets planet fertility to random value
  fertility = (rand()%(MAX_FERTILITY-MIN_FERTILITY+1) + MIN_FERTILITY);
  
  // Sets planet deposits to random value
  deposits = (rand()%(DEPOSITS_RANGE+1)) + MIN_DEPOSITS;
  
  // Sets planet status
  status = undiscovered;
}

// MARK: - Game Loop Methods

void Planet::update() {
  SDL_Point pos = uiPosition();
  destR.x = pos.x;
  destR.y = pos.y;
  
  destR.w = size.w;
  destR.h = size.h;
}

void Planet::render() {
  SDL_RenderCopy(Game::renderer, texture, NULL, &destR);
}

// MARK: - Helper Methods

SDL_Point Planet::uiPosition() {
  return Map::uiPosition(position);
}
