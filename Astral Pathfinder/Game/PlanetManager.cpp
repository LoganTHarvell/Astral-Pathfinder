//
//  PlanetManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "PlanetManager.hpp"

// MARK: Libraries and Frameworks
#include <iostream>
#include <cstdlib>
#include <ctime>

// MARK: Source Files
#include "Game.hpp"


// MARK: - Galaxy Initialization

void PlanetManager::initGalaxy() {
  using PlanetManagerParameters::numberOfPlanets;
  
  // Sees rand method
  srand((unsigned)time(NULL));
  
  int i = 0;
  bool hasPlanet[numberOfPlanets][numberOfPlanets] = { false };
  
  // Initializes first element in planets array as homeworld
  planets[i] = initHomeworld();
  // Marks planet coordinates as occupied
  hasPlanet[planets[i].getCoordinates().x][planets[i].getCoordinates().y] = true;

  // Initializes galaxy with number of planets
  for (i=1; i<numberOfPlanets; i++) {
    
    // Prevents duplicate coordinates
    do {
      planets[i] = initPlanet();
    } while (hasPlanet[planets[i].getCoordinates().x][planets[i].getCoordinates().y]);
    
    // Marks planet coordinates as occupied
    hasPlanet[planets[i].getCoordinates().x][planets[i].getCoordinates().y] = true;
  }
  
};


// Mark: - Game Loop Methods

void PlanetManager::update(ShipManager *shipManager) {
  for (Planet& p : planets) {
    p.update();
   // p.collision(shipManager->getPlayerShip().getRect());
  }
}

void PlanetManager::render() {
  for(Planet p : planets) {
    p.render();
  }
}


// MARK: - PlanetManager Methods

Planet PlanetManager::getPlanet(int n) {
  return planets[n];
}


// MARK: - Initialization Helper Methods

// Homeworld Initialization
Planet PlanetManager::initHomeworld() {
  Planet homeworld;
  
  // Initialize homeworld variables
  homeworld.initHomeworld();
  
  return homeworld;
}

// Planet Initialization
Planet PlanetManager::initPlanet() {
  Planet planet;
  
  // Initialize planet variables
  planet.initPlanet();
  
  return planet;
}

void PlanetManager::collision(SDL_Rect r) {
 // for (Planet p : planets) {
 //   p.collision(r);
 // }
}
