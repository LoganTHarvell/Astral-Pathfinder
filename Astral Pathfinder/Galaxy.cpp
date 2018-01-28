//
//  Galaxy.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

// MARK: Header File
#include "Galaxy.hpp"

// MARK: Libraries and Frameworks
#include <cstdlib>
#include <ctime>

// MARK: Source Files
#include "Game.hpp"

// TODO: Once planet rendering has moved to Map class, remove planetSrcRect
const SDL_Rect Galaxy::planetSrcRect = { 0, 0, PLANET_TEXTURE_SIZE,
                                               PLANET_TEXTURE_SIZE };


// MARK: - Galaxy Constructor/Initialization

Galaxy::Galaxy() {
  
  // Sees rand function
  srand((unsigned)time(NULL));
  
  int i = 0;
  
  // Initializes first element in planets array as homeworld
  planets[i] = initHomeworld();
  // Marks planet coordinates as occupied
  hasPlanet[planets[i].xpos][planets[i].ypos] = true;

  // Initializes galaxy with number of planets
  for (i=1; i<NUMBER_OF_PLANETS; i++) {
    
    // Prevents duplicate coordinates
    do {
      planets[i] = initPlanet();
    } while (hasPlanet[planets[i].xpos][planets[i].ypos]);
    
    // Marks planet coordinates as occupied
    hasPlanet[planets[i].xpos][planets[i].ypos] = true;
  }
  
};

Galaxy::~Galaxy() {
};


// MARK: - Galaxy Functions

void Galaxy::render() {
  
  // Renders planets game objects
  for (int i = 0; i < SDL_arraysize(planets) ; i++) {
    planets[i].gameObject->render();
  }
}

void Galaxy::update() {
  
  // Updates planets game objects
  for (int i = 0; i < NUMBER_OF_PLANETS; i++) {
    planets[i].gameObject->update();
  }
  
}


// MARK: - Planet Initialization Functions

Galaxy::Planet Galaxy::initHomeworld() {
  Planet homeworld;
  
  // Sets homeworld coordinates
  homeworld.xpos = rand()%NUMBER_OF_PLANETS;
  homeworld.ypos = rand()%NUMBER_OF_PLANETS;
  
  // Sets homeworld resources
  homeworld.fertility = STARTING_POPULATION/PEOPLE_FOOD_RQMT;
  homeworld.deposits = SHIP_COST * 2 + 50;
  
  // Initializes homeworld status to colonized
  homeworld.status = Planet::colonized;
  
  // TODO: Once planet rendering has moved to Map class, remove homeworld.gameObject
  int x = GRID_X_ORIGIN + (homeworld.xpos * GRID_WIDTH) + PLANET_TEXTURE_OFFSET_X;
  int y = GRID_Y_ORIGIN + (homeworld.ypos * GRID_HEIGHT) + PLANET_TEXTURE_OFFSET_Y;
  homeworld.gameObject = new GameObject("Resources/Assets/planet.png",
                                        planetSrcRect, x, y);
  
  return homeworld;
}

Galaxy::Planet Galaxy::initPlanet() {
  Planet planet;
  
  // Set planet coordinates
  planet.xpos = rand()%NUMBER_OF_PLANETS;
  planet.ypos = rand()%NUMBER_OF_PLANETS;
  
  // Sets planet fertility to random value
  planet.fertility = (rand()%(MAX_FERTILITY-MIN_FERTILITY+1) + MIN_FERTILITY);
  // Sets planet deposits to random value
  planet.deposits = (rand()%(DEPOSITS_RANGE+1)) + MIN_DEPOSITS;
  
  // Initializes planet status to undiscovered
  planet.status = Planet::undiscovered;
  
  // TODO: Once planet rendering has moved to Map class, remove planet.gameObject
  int x = GRID_X_ORIGIN + (planet.xpos * GRID_WIDTH) + PLANET_TEXTURE_OFFSET_X;
  int y = GRID_Y_ORIGIN + (planet.ypos * GRID_HEIGHT) + PLANET_TEXTURE_OFFSET_Y;
  planet.gameObject = new GameObject("Resources/Assets/planet.png",
                                     planetSrcRect, x, y);
  
  return planet;
}
