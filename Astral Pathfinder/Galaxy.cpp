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
#include <stdlib.h>
#include <time.h>

// MARK: Source Files
#include "Game.hpp"

const SDL_Rect Galaxy::planetSrcRect = { 0, 0, PLANET_TEXTURE_SIZE,
                                               PLANET_TEXTURE_SIZE };

Galaxy::Galaxy() {
  
  srand((unsigned)time(NULL));
  
  int i = 0;
  planets[i] = initHomeworld();
  hasPlanet[planets[i].xpos][planets[i].ypos] = true;

  for (i=1; i<NUMBER_OF_PLANETS; i++) {
    do {
      planets[i] = initPlanet();
    } while (hasPlanet[planets[i].xpos][planets[i].ypos]);
    
    hasPlanet[planets[i].xpos][planets[i].ypos] = true;
  }
  
};

Galaxy::~Galaxy() {
};

void Galaxy::render() {
  for (int i = 0; i < NUMBER_OF_PLANETS; i++) {
    planets[i].gameObject->render();
  }
}

void Galaxy::update() {
  for (int i = 0; i < NUMBER_OF_PLANETS; i++) {
    planets[i].gameObject->update();
  }
}

Galaxy::Planet Galaxy::initHomeworld() {
  Planet homeworld;
  
  //sets homeworld coordinates
  homeworld.xpos = rand()%NUMBER_OF_PLANETS;
  homeworld.ypos = rand()%NUMBER_OF_PLANETS;
  
  //sets homeworld resources
  homeworld.fertility = STARTING_POPULATION/PEOPLE_FOOD_RQMT;
  homeworld.deposits = SHIP_COST * 2 + 50;
  //initializes homeworld max population to starting population
  homeworld.status = Planet::colonized;
  
  // initializes game object
  int x = MAP_X_ORIGIN + (homeworld.xpos * GRID_SIZE) + PLANET_TEXTURE_OFFSET;
  int y = MAP_Y_ORIGIN + (homeworld.ypos * GRID_SIZE) + PLANET_TEXTURE_OFFSET;
  homeworld.gameObject = new GameObject("Resources/Assets/planet.png",
                                        planetSrcRect, x, y);
  
  return homeworld;
}

Galaxy::Planet Galaxy::initPlanet() {
  Planet planet;
  
  //set planet coordinates
  planet.xpos = rand()%NUMBER_OF_PLANETS;
  planet.ypos = rand()%NUMBER_OF_PLANETS;
  
  //sets planet fertility to random value
  planet.fertility = (rand()%(MAX_FERTILITY-MIN_FERTILITY+1) + MIN_FERTILITY);
  //sets planet deposits to random value
  planet.deposits = (rand()%(DEPOSITS_RANGE+1)) + MIN_DEPOSITS;
  
  //initializes max population to 0
  planet.status = Planet::undiscovered;
  
  // initializes game object
  int x = MAP_X_ORIGIN + (planet.xpos * GRID_SIZE) + PLANET_TEXTURE_OFFSET;
  int y = MAP_Y_ORIGIN + (planet.ypos * GRID_SIZE) + PLANET_TEXTURE_OFFSET;
  planet.gameObject = new GameObject("Resources/Assets/planet.png",
                                     planetSrcRect, x, y);
  
  return planet;
}
