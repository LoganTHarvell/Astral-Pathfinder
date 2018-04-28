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
  
  playerDockedPlanetIndex = 0;      // Start with homeworld docked
  selectedPlanetIndex = -1;   // Start with no planet selected
  discoveryCount = 1;         // Start with 1 colonized planet

};


// Mark: - Game Loop Methods

void PlanetManager::update(Game::State *gameState, ShipManager *shipManager) {
  // Checks for any collisions first
  handleCollisions(shipManager, gameState->frame);
  gameState->planetCollided = playerIsDocked();
  
  // Updates each planet, also refreshes count of discovered planets
  totalPopulation = 0;
  discoveryCount = 0;
  for (Planet& p : planets) {
    totalPopulation += p.getPopulation();
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

int PlanetManager::getTotalPopulation() {
  return totalPopulation;
}

Planet PlanetManager::getPlanet(int n) {
  return planets[n];
}

Planet PlanetManager::getSelectedPlanet() {
  return planets[selectedPlanetIndex];
}

bool PlanetManager::playerIsDocked() {
  if (playerDockedPlanetIndex >= 0) return true;
  return false;
}

Planet PlanetManager::getPlayerDockedPlanet() {
  return planets[playerDockedPlanetIndex];
}

// TODO: Use enum for readability of flags
void PlanetManager::setPlanetMiningPercent(int p, int flag) {
  if(flag == dockedPlanet)
    planets[playerDockedPlanetIndex].setMiningPercent(p);
  if(flag == selectedPlanet)
    planets[selectedPlanetIndex].setMiningPercent(p);
}

void PlanetManager::setPlanetFarmingPercent(int p, int flag) {
  if(flag == dockedPlanet)
    planets[playerDockedPlanetIndex].setFarmingPercent(p);
  if(flag == selectedPlanet)
    planets[selectedPlanetIndex].setFarmingPercent(p);
}

void PlanetManager::setPlanetInfraPercent(int p, int flag) {
  if(flag == dockedPlanet)
    planets.at(playerDockedPlanetIndex).setInfraPercent(p);
  if(flag == selectedPlanet)
    planets.at(selectedPlanetIndex).setInfraPercent(p);
}

void PlanetManager::setPlanetReservePercent(int p, int flag) {
  if(flag == dockedPlanet)
    planets.at(playerDockedPlanetIndex).setReservePercent(p);
  if(flag == selectedPlanet)
    planets.at(selectedPlanetIndex).setReservePercent(p);
}

// TODO: Implement actual fuel algorithm
int PlanetManager::fuelDockedShip() {
  int fuel = 0;
  
  int amount = planets[playerDockedPlanetIndex].getMinerals();
  fuel = planets[playerDockedPlanetIndex].makeFuel(amount);
  
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

void PlanetManager::handleCollisions(ShipManager *sm, Uint32 frame) {
  Ship player = sm->getPlayerShip();
  std::vector<SDL_Point> playerVertices = player.getCollider().getVertices();
  
  // Checks all planets for collisions if player ship hasn't docked
  if (playerDockedPlanetIndex < 0) {
    for (int i = 0; i < planets.size(); i++) {
      if (planets[i].getCollider().collisionOBB(playerVertices)) {
        planets[i].toggleDockedShip(player.getTag(), frame);
        playerDockedPlanetIndex = i;
        std::cout << "Collision at: "
                  << planets[i].getCoordinates().x << ","
                  << planets[i].getCoordinates().y << std::endl;
      }
    }
  }
  // If player has docked checks docked planet for continued collision
  else {
    ColliderComponent collider = planets[playerDockedPlanetIndex].getCollider();
    if (!collider.collisionOBB(playerVertices)) {
      planets[playerDockedPlanetIndex].toggleDockedShip(player.getTag(), frame);
      playerDockedPlanetIndex = -1;
    }
  }
}
