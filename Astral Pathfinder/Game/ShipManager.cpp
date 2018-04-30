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
//  oldTarget = p;
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
  
  if (playerShip.getFuel() <= 0 && !pm->playerIsDocked()) {
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
//  SDL_Point targetPos = alienShip.getTarget();
  
  if (dockedPos.x == mainTargetPos.x && dockedPos.y == mainTargetPos.y) {
    int randPlanetIndex = rand()%PlanetManagerParameters::numberOfPlanets;
    Planet randPlanet = pm->getPlanet(randPlanetIndex);
    alienShip.setMainTarget(randPlanet.getCenter());
    alienShip.resetTarget();
  }
//  else if (dockedPos.x == targetPos.x && dockedPos.y == targetPos.y) {
//    oldTarget = targetPos;
//    alienShip.resetTarget();
//  }
//  else {
//    double minDistance = 60;
//    Planet targetP;
//    bool targetPInit = false;
//
//    for (int i=0; i < PlanetManagerParameters::numberOfPlanets; i++) {
//      Planet p = pm->getPlanet(i);
//      SDL_Point pCenter = p.getCenter();
//      ColliderComponent alienCollider = alienShip.getCollider();
//
//      if (p.getCenter().x == oldTarget.x && p.getCenter().y == oldTarget.y) {
//        continue;
//      }
  
//      if (gs->frame%ShipManagerParameters::alienTargetingDelay != 0) {
//        continue;
//      }
      
//      if (alienCollider.collisionCircle(30, p.getCollider().getVertices())) {
//        double d = sqrt((pCenter.x-dockedPos.x)^2 + (pCenter.y-dockedPos.y)^2);
//        if (d < minDistance) {
//          minDistance = d;
//          targetP = p;
//          targetPInit = true;
//        }
      
//        alienShip.updateTarget(p.getCenter());
//        oldTarget = p.getCenter();
//      }
//    }
//
//    if (targetPInit) {
//      alienShip.updateTarget(targetP.getCenter());
//    }
//  }
  
}
