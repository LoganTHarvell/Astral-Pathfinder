//
//  Galaxy.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "PlanetManager.hpp"

// MARK: Libraries and Frameworks
#include <cstdlib>
#include <ctime>

// MARK: Source Files
#include "Game.hpp"


// MARK: - Galaxy Initialization

void PlanetManager::initGalaxy() {
  
  // Sees rand function
  srand((unsigned)time(NULL));
  
  int i = 0;
  bool hasPlanet[NUMBER_OF_PLANETS][NUMBER_OF_PLANETS] = { false };
  
  // Initializes first element in planets array as homeworld
  planets[i] = initHomeworld();
  // Marks planet coordinates as occupied
  hasPlanet[planets[i].getPositionX()][planets[i].getPositionY()] = true;

  // Initializes galaxy with number of planets
  for (i=1; i<NUMBER_OF_PLANETS; i++) {
    
    // Prevents duplicate coordinates
    do {
      planets[i] = initPlanet();
    } while (hasPlanet[planets[i].getPositionX()][planets[i].getPositionY()]);
    
    // Marks planet coordinates as occupied
    hasPlanet[planets[i].getPositionX()][planets[i].getPositionY()] = true;
  }
  
};


// MARK: - Planet Initialization Functions

Planet PlanetManager::initHomeworld() {
  Planet homeworld;
  
  // Initialize homeworld variables
  homeworld.initHomeworld();
  
  return homeworld;
}

Planet PlanetManager::initPlanet() {
  Planet planet;
  
  // Initialize planet variables
  planet.initPlanet();
  
  return planet;
}
