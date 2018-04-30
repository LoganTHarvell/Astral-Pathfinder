//
//  ShipManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "ShipManager.hpp"


// MARK: - ShipManager Initialization

void ShipManager::init(SDL_Point homeworldPos, SDL_Point alienPos) {
  using namespace ShipParameters;
  
  // Centers ship on homeworld
  SDL_Point p;
  p.x = homeworldPos.x - (shipSize.w/2);
  p.y = homeworldPos.y - (shipSize.h/2);

  playerShip.init(p);

  p.x = alienPos.x - (shipSize.w/2);
  p.y = alienPos.y - (shipSize.h/2);
  
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
  
  if (playerShip.getFuel() <= 0 && pm->playerIsDocked()
      && pm->getPlayerDockedPlanet().getMinerals() <= 0) {
    gameState->endgame = Game::State::noFuel;
  }
  else if (pCollider.collisionOBB(aCollider.getVertices())) {
    gameState->endgame = Game::State::alienAttack;
  }
}

void ShipManager::render(Game::State *gameState) {
  playerShip.render(gameState);
  alienShip.render(gameState);
  
  if (gameState->debugMode) {
    DebugTools::renderVertices(playerShip.getCollider().getVertices());
    DebugTools::renderVertices(alienShip.getCollider().getVertices());
  }
}

void ShipManager::setAlienTarget(Game::State *gs, PlanetManager *pm) {
  
  SDL_Point dockedPos = alienShip.getCenter();
  SDL_Point mainTargetPos = alienShip.getMainTarget();
  
  if (dockedPos.x == mainTargetPos.x && dockedPos.y == mainTargetPos.y) {
    int randPlanetIndex = rand()%PlanetManagerParameters::numberOfPlanets;
    Planet randPlanet = pm->getPlanet(randPlanetIndex);
    alienShip.setMainTarget(randPlanet.getCenter());
    alienShip.resetTarget();
  }

  
}
