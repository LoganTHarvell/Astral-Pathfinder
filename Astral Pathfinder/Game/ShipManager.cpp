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

void ShipManager::update() {
  playerShip.update();
}

void ShipManager::render() {
  playerShip.render();
}

void ShipManager::shipMovement(SDL_Event e) {
  using ShipParameters::velocity;
  SDL_Point temp;
  switch(e.key.keysym.sym) {
    case SDLK_UP:
      temp = { 0, -velocity };
      playerShip.updatePosition(temp);
      break;
    case SDLK_RIGHT:
      temp = { velocity, 0 };
      playerShip.updatePosition(temp);
      break;
    case SDLK_DOWN:
      temp = { 0, velocity };
      playerShip.updatePosition(temp);
      break;
    case SDLK_LEFT:
      temp = { -velocity, 0 };
      playerShip.updatePosition(temp);
      break;
    default:
      break;
  }
}
