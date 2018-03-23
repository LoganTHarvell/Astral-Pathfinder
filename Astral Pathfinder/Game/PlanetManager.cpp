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
  
  bool hasPlanet[numberOfPlanets][numberOfPlanets] = { false };
  
  // Initializes first element in planets array as homeworld
  planets.insert(planets.begin(), initHomeworld());
  
  // Marks planet coordinates as occupied
  SDL_Point coordinates = planets.front().getCoordinates();
  hasPlanet[coordinates.x][coordinates.y] = true;

  // Initializes galaxy with number of planets
  while (planets.size() < numberOfPlanets) {
    // Prevents duplicate coordinates
    auto i = planets.end();
    do {
      i = planets.insert(i, initPlanet());
      coordinates = i->getCoordinates();
      
      // Clears index for new planet
      if (hasPlanet[coordinates.x][coordinates.y]) planets.erase(i);
      
    } while (hasPlanet[coordinates.x][coordinates.y]);

    // Marks planet coordinates as occupied
    hasPlanet[coordinates.x][coordinates.y] = true;
  }
  
  dockedPlanetIndex = 0;      // Start with homeworld docked
  selectedPlanetIndex = -1;   // Start with no planet selected
  discoveryCount = 1;         // Start with 1 colonized planet

};


// Mark: - Game Loop Methods

void PlanetManager::update(Game::State *gameState, ShipManager *shipManager) {
  // Updates each planet, also refreshes count of discovered planets
  discoveryCount = 0;
  for (Planet& p : planets) {
    if (p.getStatus() != Planet::undiscovered) discoveryCount++;
    p.update(gameState);
  }
  
  // Checks all planets discovered endgame condition
  if (discoveryCount == PlanetManagerParameters::numberOfPlanets)
    gameState->endgame = Game::State::allDiscovered;
  
  // Deselects a previously selected planet when selection ends
  if (!gameState->planetSelected && selectedPlanetIndex >= 0) {
    deselectPlanet(&(gameState->planetSelected));
  }

  if (gameState->clickFlag) {
    handleClickEvent(gameState->clickLocation, gameState);
    gameState->clickFlag = false;
  }
  
  handleCollisions(shipManager);
  gameState->planetCollided = planetIsDocked();
}

void PlanetManager::render(Game::State *gameState) {
  for(Planet p : planets) {
    p.render(gameState);
    
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

bool PlanetManager::planetIsDocked() {
  if (dockedPlanetIndex >= 0) return true;
  return false;
}

Planet PlanetManager::getDockedPlanet() {
  return planets[dockedPlanetIndex];
}

void PlanetManager::setPlanetDepoPercent(int p, int flag) {
  if(flag == 1)
    planets[dockedPlanetIndex].setDepositsPercent(p);
  if(flag == 2)
    planets[selectedPlanetIndex].setDepositsPercent(p);
}

void PlanetManager::setPlanetFertPercent(int p, int flag) {
  if(flag == 1)
    planets[dockedPlanetIndex].setFertilityPercent(p);
  if(flag == 2)
    planets[selectedPlanetIndex].setFertilityPercent(p);
}

void PlanetManager::setPlanetInfraPercent(int p, int flag) {
  if(flag == 1)
    planets.at(dockedPlanetIndex).setInfraPercent(p);
  if(flag == 2)
    planets.at(selectedPlanetIndex).setInfraPercent(p);
}

void PlanetManager::setPlanetReservePercent(int p, int flag) {
  if(flag == 1)
    planets.at(dockedPlanetIndex).setReservePercent(p);
  if(flag == 2)
    planets.at(selectedPlanetIndex).setReservePercent(p);
}

// TODO: Implement actual fuel algorithm
int PlanetManager::fuelDockedShip() {
  int fuel = 0;
  
  int amount = planets[dockedPlanetIndex].getMinerals();
  fuel = planets[dockedPlanetIndex].makeFuel(amount);
  
  return fuel;
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
      
      if (planet.getStatus() != Planet::undiscovered || gs->debugMode) {
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
        planets[i].toggleDockedShip(player.getTag());
        dockedPlanetIndex = i;
        std::cout << "Collision at: "
                  << planets[i].getCoordinates().x << ","
                  << planets[i].getCoordinates().y << std::endl;
      }
    }
  }
  // If player has docked checks docked planet for continued collision
  else {
    ColliderComponent collider = planets[dockedPlanetIndex].getCollider();
    if (!collider.collisionOBB(playerVertices, playerAngle)) {
      planets[dockedPlanetIndex].toggleDockedShip(player.getTag());
      dockedPlanetIndex = -1;
    }
  }
}
