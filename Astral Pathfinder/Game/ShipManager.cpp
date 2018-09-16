//
//  ShipManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Manager class responsible for managing all ship gameObjects, specifically
//  initializing, updating, and rendering. Also handles ship based endgame
//  conditions.

// MARK: Header File
#include "ShipManager.hpp"


// MARK: - ShipManager Initialization

void ShipManager::init(SDL_Point homeworldPos, SDL_Point alienPos) {
  
  // Centers ship on homeworld
  SDL_Point p;
  p.x = homeworldPos.x - (Parameters::Ship::shipRect.w/2);
  p.y = homeworldPos.y - (Parameters::Ship::shipRect.h/2);

  playerShip.init(p);

  p.x = alienPos.x - (Parameters::Ship::shipRect.w/2);
  p.y = alienPos.y - (Parameters::Ship::shipRect.h/2);
  
  alienShip.init(p);
}

// MARK: - Game Loop Methods

void ShipManager::update(Game::State *gameState, PlanetManager *pm) {
  playerShip.update(gameState);
  alienShip.update(gameState);
  
  setAlienTarget(gameState, pm);
  
  if (pm->playerIsDocked()) playerShip.updateFuel(pm->fuelDockedShip());
  
  // Endgame checks
  ColliderComponent pCollider = playerShip.getCollider();
  ColliderComponent aCollider = alienShip.getCollider();
  
  if (playerShip.getFuel() <= 0) {
    if (!pm->playerIsDocked()) {
      gameState->endgame = Game::State::noFuel;
    }
    else if (pm->getPlayerDockedPlanet().getDeposits() <= 0) {
      gameState->endgame = Game::State::noFuel;
    }
  }
  else if (pCollider.collisionOBB(aCollider.getVertices())) {
    gameState->endgame = Game::State::alienAttack;
  }
}

void ShipManager::render(Game::State *gameState) {
  playerShip.render(gameState);
  alienShip.render(gameState);
  
  if (gameState->debugMode) {
    DebugTools::renderVertices(playerShip.getCollider().getVertices(),
                               Game::renderer);
    DebugTools::renderVertices(alienShip.getCollider().getVertices(),
                               Game::renderer);
  }
}

// Sets Alien warship target by randomly selecting planet
void ShipManager::setAlienTarget(Game::State *gs, PlanetManager *pm) {
  
  SDL_Point dockedPos = alienShip.getCenter();
  SDL_Point mainTargetPos = alienShip.getMainTarget();
  
  if (dockedPos.x == mainTargetPos.x && dockedPos.y == mainTargetPos.y) {
    int randPlanetIndex = rand()%Parameters::PlanetManager::numberOfPlanets;
    Planet randPlanet = pm->getPlanet(randPlanetIndex);
    alienShip.setMainTarget(randPlanet.getCenter());
    alienShip.resetTarget();
  }

  
}
