//
//  Ship.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Ship.hpp"

// MARK: Source Files
#include "Game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"


// MARK: - Initialization Methods

void Ship::init(SDL_Point p) {
  using namespace ShipParameters;
  
  position = p;
  size = { shipSize.w, shipSize.h };
  texture = TextureManager::loadTexture("Resources/Assets/simpleSpaceship.png");
  
  rotation = 0;
  fuel = 0;
}


// MARK: - Game Loop Methods

void Ship::update() {
  SDL_Point pos = uiPosition();
  destR.x = pos.x;
  destR.y = pos.y;
  
  destR.w = size.w;
  destR.h = size.h;
}

void Ship::render() {
  SDL_RenderCopy(Game::renderer, texture, NULL, &destR);
}


// MARK: - Helper Methods

SDL_Point Ship::uiPosition() {
  return Map::uiPosition(position);
}
