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
  
  planets.reserve(sizeof(Planet) * numberOfPlanets);
  
  // Sees rand method
  srand((unsigned)time(NULL));
  
  bool hasPlanet[numberOfPlanets][numberOfPlanets] = { false };
  
  // Initializes first element in planets array as homeworld
  auto i = planets.begin();
  planets.emplace(i, initHomeworld());
  
  // Marks planet coordinates as occupied
  SDL_Point coordinates = i->getCoordinates();
  hasPlanet[coordinates.x][coordinates.y] = true;

  // Initializes galaxy with number of planets
  while (planets.size() < numberOfPlanets) {
    // Prevents duplicate coordinates
    auto tmp = i;
    do {
      tmp = planets.emplace(i, initPlanet());
      coordinates = i->getCoordinates();
    } while (hasPlanet[coordinates.x][coordinates.y]);
    i = tmp;

    // Marks planet coordinates as occupied
    hasPlanet[coordinates.x][coordinates.y] = true;
  }
  
  dockedPlanetIndex = selectedPlanetIndex = -1;

};


// Mark: - Game Loop Methods

void PlanetManager::update(Game::State *gameState, ShipManager *shipManager) {
  for (Planet& p : planets) p.update();
  
  if (!gameState->planetSelected && selectedPlanetIndex >= 0) {
    deselectPlanet(&(gameState->planetSelected));
  }
  
  if (gameState->clickFlag) {
    handleClickEvent(gameState->clickLocation, gameState);
    gameState->clickFlag = false;
  }
  
  handleCollisions(shipManager);
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
  return planets.at(n);
}

Planet PlanetManager::getSelectedPlanet() {
  return planets.at(selectedPlanetIndex);
}

void PlanetManager::setPlanetDepoPercent(int p) {
  planets.at(selectedPlanetIndex).setDepositsPercent(p);
}

void PlanetManager::setPlanetFertPercent(int p) {
  planets.at(selectedPlanetIndex).setFertilityPercent(p);
}

void PlanetManager::setPlanetInfraPercent(int p) {
  planets.at(selectedPlanetIndex).setInfraPercent(p);
}

void PlanetManager::setPlanetReservePercent(int p) {
  planets.at(selectedPlanetIndex).setReservePercent(p);
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

void PlanetManager::handleClickEvent(SDL_Point p, Game::State *gs) {
  // Checks for planet selection
  int i = 0;
  for(Planet planet : planets) {
    SDL_Rect temp = planet.getRect();
    
    if((p.x > temp.x) && (p.x < temp.x + temp.w)
       && (p.y > temp.y) && (p.y < temp.y + temp.h)) {
      
      if (selectedPlanetIndex >= 0) deselectPlanet(&gs->planetSelected);
      
      if (planet.getStatus() == Planet::discovered || gs->debugMode) {
        selectedPlanetIndex = i;
        selectPlanet(&gs->planetSelected);
      }
      else
        selectedPlanetIndex = -1;
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

void PlanetManager::handleCollisions(ShipManager *sm) {
  Ship player = sm->getPlayerShip();
  std::vector<SDL_Point> playerVertices = player.getCollider().getVertices();
  int playerAngle = player.getRotation();
  
  // Checks all planets for collisions if player ship hasn't docked
  if (dockedPlanetIndex < 0) {
    for (int i = 0; i < planets.size(); i++) {
      if (planets[i].getCollider().collisionOBB(playerVertices, playerAngle)) {
        planets.at(i).toggleDockedShip(player.getTag());
        dockedPlanetIndex = i;
        std::cout << "Collision at: "
                  << planets.at(i).getCoordinates().x << ","
                  << planets.at(i).getCoordinates().y << std::endl;
      }
    }
  }
  // If player has docked checks docked planet for continued collision
  else {
    ColliderComponent collider = planets[dockedPlanetIndex].getCollider();
    if (!collider.collisionOBB(playerVertices, playerAngle)) {
      planets.at(dockedPlanetIndex).toggleDockedShip(player.getTag());
      dockedPlanetIndex = -1;
    }
  }
}
