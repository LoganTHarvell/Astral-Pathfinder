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
#include "ShipManager.hpp"

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

void PlanetManager::update(Game::State *gameState, ShipManager *shipManager) {
  for (Planet& p : planets) {
    p.update();
    
    // TODO: Remove and implement collision logic
    auto ship = shipManager->getPlayerShip();
    auto shipVertices = ship.getCollider().getVertices();
    auto shipAngle = ship.getRotation();
    p.getCollider().collisionOBB(shipVertices, shipAngle);
  }
  
  if (!gameState->planetSelected && selectedPlanetIndex >= 0) {
    deselectPlanet(&(gameState->planetSelected));
  }
  
  if (gameState->clickFlag) {
    handleClickEvent(gameState->clickLocation, &(gameState->planetSelected));
    gameState->clickFlag = false;
  }
  
}

void PlanetManager::render(Game::State *gameState) {
  for(Planet p : planets) {
    p.render();
    
    if (gameState->debugMode) {
      DebugTools::renderVertices(p.getCollider().getVertices());
    }
  }
}


// MARK: - PlanetManager Methods

Planet PlanetManager::getPlanet(int n) {
  return planets[n];
}

Planet PlanetManager::getSelectedPlanet() {
  return planets[selectedPlanetIndex];
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

void PlanetManager::handleClickEvent(SDL_Point p, bool *planetSelected) {
  
  int i = 0;
  for(Planet planet : planets) {
    SDL_Rect temp = planet.getRect();
    
    if((p.x > temp.x) && (p.x < temp.x + temp.w)
       && (p.y > temp.y) && (p.y < temp.y + temp.h)) {
      
      if (selectedPlanetIndex >= 0) deselectPlanet(planetSelected);
      
      selectedPlanetIndex = i;
      selectPlanet(planetSelected);
    }
    
    i++;
  }
  
}

void PlanetManager::selectPlanet(bool *planetSelected) {
  planets[selectedPlanetIndex].clicked();
  *planetSelected = true;
}

void PlanetManager::deselectPlanet(bool *planetSelected) {
  planets[selectedPlanetIndex].revertClick();
  selectedPlanetIndex = -1;
  *planetSelected = false;
}

void PlanetManager::collision(std::vector<SDL_Point> vertices, int angle) {
  for (Planet p : planets) {
    p.getCollider().collisionOBB(vertices, angle);
  }
}
