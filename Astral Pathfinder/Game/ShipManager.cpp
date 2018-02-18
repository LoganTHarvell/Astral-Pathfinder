//
//  ShipManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "ShipManager.hpp"


// MARK: - ShipManager Initialization

void ShipManager::init(SDL_Point homeworldPos) {
  playerShip.init(homeworldPos);
}

// MARK: - Game Loop Methods

void ShipManager::update(Uint32 ticks) {
  // TODO: see ship update comment; we don't want to call move
  playerShip.update();
  playerShip.move(ticks);
}

void ShipManager::render() {
  playerShip.render();
}

void ShipManager::shipMovement(SDL_Event e) {
  playerShip.updateVelocity(e);
}
