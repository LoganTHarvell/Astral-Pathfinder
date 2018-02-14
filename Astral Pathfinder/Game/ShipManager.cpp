//
//  ShipManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "ShipManager.hpp"

void ShipManager::init(SDL_Point homeworldPos) {
  playerShip.init(homeworldPos);
}

void ShipManager::update() {
  playerShip.update();
}

void ShipManager::render() {
  playerShip.render();
}
