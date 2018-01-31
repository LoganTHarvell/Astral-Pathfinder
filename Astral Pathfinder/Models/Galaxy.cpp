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
  hasPlanet[planets[i].position.x][planets[i].position.y] = true;

  // Initializes galaxy with number of planets
  for (i=1; i<NUMBER_OF_PLANETS; i++) {
    
    // Prevents duplicate coordinates
    do {
      planets[i] = initPlanet();
    } while (hasPlanet[planets[i].position.x][planets[i].position.y]);
    
    // Marks planet coordinates as occupied
    hasPlanet[planets[i].position.x][planets[i].position.y] = true;
  }
  
};

Galaxy::~Galaxy() {
};


// MARK: - Planet Initialization Functions

Galaxy::Planet Galaxy::initHomeworld() {
  Planet homeworld;
  
  // Sets homeworld coordinates
  homeworld.position.x = rand()%NUMBER_OF_PLANETS;
  homeworld.position.y = rand()%NUMBER_OF_PLANETS;
  
  // Sets homeworld resources
  homeworld.fertility = STARTING_POPULATION/PEOPLE_FOOD_RQMT;
  homeworld.deposits = SHIP_COST * 2 + 50;
  
  // Initializes homeworld status to colonized
  homeworld.status = Planet::colonized;
  
  return homeworld;
}

Galaxy::Planet Galaxy::initPlanet() {
  Planet planet;
  
  // Set planet coordinates
  planet.position.x = rand()%NUMBER_OF_PLANETS;
  planet.position.y = rand()%NUMBER_OF_PLANETS;
  
  // Sets planet fertility to random value
  planet.fertility = (rand()%(MAX_FERTILITY-MIN_FERTILITY+1) + MIN_FERTILITY);
  // Sets planet deposits to random value
  planet.deposits = (rand()%(DEPOSITS_RANGE+1)) + MIN_DEPOSITS;
  
  // Initializes planet status to undiscovered
  planet.status = Planet::undiscovered;
  
  return planet;
}
