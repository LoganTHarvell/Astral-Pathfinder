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

void ShipManager::init(SDL_Point homeworldPos) {
  using namespace ShipParameters;
  
  // Centers ship on homeworld
  SDL_Point p = { homeworldPos.x - (shipSize.w/2),
                  homeworldPos.y - (shipSize.h/2) };
  
  playerShip.init(p, ShipType::playerShip);
}

// MARK: - Game Loop Methods

void ShipManager::update(Uint32 ticks) {
  // TODO: Put ticks in GameState then add GameState to update parameters
  playerShip.update();
  playerShip.move(ticks);
}

void ShipManager::render(Game::State *gameState) {
  playerShip.render();
  
  if (gameState->debugMode) {
    DebugTools::renderVertices(playerShip.getCollider().getVertices());
  }
}
