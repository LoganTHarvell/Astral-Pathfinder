//
//  PlanetManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Manager class responsible for managing all planet gameObjects, specifically
//  initializing, updating, and rendering. Also planet click interactions,
//  planet-ship interactions, docking info, and planet based endgame conditions.

// MARK: Header File
#include "PlanetManager.hpp"

// MARK: Libraries and Frameworks
#include <map>
#include <iostream>
#include <cstdlib>
#include <ctime>

// MARK: Source Files
#include "ShipManager.hpp"

// MARK: Aliases
using PlanetList = std::vector<Planet>;


// MARK: - Galaxy Initialization

void PlanetManager::initGalaxy() {
  using Parameters::PlanetManager::numberOfPlanets;
  
  planets.reserve(sizeof(Planet) * numberOfPlanets);
  
  std::map<std::pair<int, int>, bool> hasPlanet;
  
  // Initializes first element in planets array as homeworld
  planets.insert(planets.begin(), initHomeworld());
  
  // Marks planet coordinates as occupied
  SDL_Point tmp = planets.front().getCoordinates();
  std::pair<int, int> coordinates = { tmp.x, tmp.y };
  hasPlanet.emplace(coordinates, true);

  // Initializes galaxy with number of planets
  while (planets.size() < numberOfPlanets) {
    // Prevents duplicate coordinates
    auto i = planets.end();
    do {
      i = planets.insert(i, initPlanet());
      
      tmp = i->getCoordinates();
      coordinates = { tmp.x, tmp.y };
      
      // Clears index for new planet
      if (hasPlanet[coordinates]) planets.erase(i);
      
    } while (hasPlanet[coordinates]);

    // Marks planet coordinates as occupied
    hasPlanet[coordinates] = true;
  }
  
  playerDockedPlanetIndex = 0;      // Start with homeworld docked
  alienDockedPlanetIndex = 1;       // Start with second planet docked
  selectedPlanetIndex = -1;         // Start with no planet selected
  discoveryCount = 1;               // Start with 1 colonized planet

  for (PlanetList::iterator it = planets.begin(); it != planets.end(); ++it) {
    planetEvents.push_back(it->getEvents());
  }
};


// Mark: - Game Loop Methods

void PlanetManager::update(Game::State *gameState, ShipManager *shipManager) {
  
  // Checks for any collisions first
  handleCollisions(shipManager, gameState->frame);
  gameState->playerCollision = playerIsDocked();
  gameState->alienCollision = alienIsDocked();
  
  // Updates each planet, also refreshes count of discovered planets
  totalPopulation = 0;
  discoveryCount = 0;
  int count = 0;
  for (Planet& p : planets) {
    totalPopulation += p.getPopulation();
    if (p.getStatus() != Planet::undiscovered) discoveryCount++;
    p.update(gameState);
    planetEvents[count] = p.getEvents();
    count++;
  }

  // Checks all planets discovered endgame condition
  if (discoveryCount == Parameters::PlanetManager::numberOfPlanets) {
    gameState->endgame = Game::State::allDiscovered;
  }
  
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
  for (Planet p : planets) {
    p.render(gameState);
  
    if (gameState->debugMode) {
      p.getCollider().renderVertices(Game::renderer);
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

bool PlanetManager::alienIsDocked() {
  if (alienDockedPlanetIndex >= 0) return true;
  return false;
}

Planet PlanetManager::getPlayerDockedPlanet() {
  return planets[playerDockedPlanetIndex];
}

Planet PlanetManager::getAlienDockedPlanet() {
  return planets[alienDockedPlanetIndex];
}

void PlanetManager::setPlanetMiningPercent(int p, int flag) {
  if (flag == dockedPlanet)
    planets[playerDockedPlanetIndex].setMiningPercent(p);
  if (flag == selectedPlanet)
    planets[selectedPlanetIndex].setMiningPercent(p);
}

void PlanetManager::setPlanetFarmingPercent(int p, int flag) {
  if (flag == dockedPlanet)
    planets[playerDockedPlanetIndex].setFarmingPercent(p);
  if (flag == selectedPlanet)
    planets[selectedPlanetIndex].setFarmingPercent(p);
}

void PlanetManager::setPlanetInfraPercent(int p, int flag) {
  if (flag == dockedPlanet)
    planets.at(playerDockedPlanetIndex).setInfraPercent(p);
  if (flag == selectedPlanet)
    planets.at(selectedPlanetIndex).setInfraPercent(p);
}

void PlanetManager::setPlanetReservePercent(int p, int flag) {
  if (flag == dockedPlanet)
    planets.at(playerDockedPlanetIndex).setReservePercent(p);
  if (flag == selectedPlanet)
    planets.at(selectedPlanetIndex).setReservePercent(p);
}

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
  for (Planet planet : planets) {
    SDL_Rect temp = planet.getRect();
    
    if ((p.x > temp.x) && (p.x < temp.x + temp.w)
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
  
  PlayerShip player = sm->getPlayerShip();
  AlienShip alien = sm->getAlienShip();
  std::vector<SDL_Point> playerVertices = player.getCollider().getVertices();
  std::vector<SDL_Point> alienVertices = alien.getCollider().getVertices();

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
  
  // Checks all planets for collisions if alien ship hasn't docked
  if (alienDockedPlanetIndex < 0) {
    for (int i = 0; i < planets.size(); i++) {
      if (planets[i].getCollider().collisionOBB(alienVertices)) {
        planets[i].toggleDockedShip(alien.getTag(), frame);
        alienDockedPlanetIndex = i;
        std::cout << "Alien collision at: "
        << planets[i].getCoordinates().x << ","
        << planets[i].getCoordinates().y << std::endl;
      }
    }
  }
  // If alien has docked checks docked planet for continued collision
  else {
    
    ColliderComponent collider = planets[alienDockedPlanetIndex].getCollider();
    
    if (!collider.collisionOBB(alienVertices)) {
      planets[alienDockedPlanetIndex].toggleDockedShip(alien.getTag(), frame);
      alienDockedPlanetIndex = -1;
    }
  
  }

}
