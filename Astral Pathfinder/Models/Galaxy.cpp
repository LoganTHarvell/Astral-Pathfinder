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


// MARK: - Galaxy Constructor/Initialization

Galaxy::Galaxy() {
  
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

Galaxy::~Galaxy() {
};


// MARK: - Planet Initialization Functions

Planet Galaxy::initHomeworld() {
  Planet homeworld;
  
  // Initialize homeworld variables
  homeworld.initHomeworld();
  
  return homeworld;
}

Planet Galaxy::initPlanet() {
  Planet planet;
  
  // Initialize planet variables
  planet.initPlanet();
  
  return planet;
}
