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
  
  position = uiPosition(p);
  size = { shipSize.w, shipSize.h };

  texture = TextureManager::loadTexture("Resources/Assets/simpleSpaceship.png");
  
  rotation = 0;
  fuel = 0;
}


// MARK: - Game Loop Methods

void Ship::update() {
  destR.x = position.x;
  destR.y = position.y;
  
  destR.w = size.w;
  destR.h = size.h;
}

void Ship::render() {
  SDL_RenderCopy(Game::renderer, texture, NULL, &destR);
}


// MARK: - Helper Methods

void Ship::updatePosition(SDL_Point p) {
  position.x += p.x;
  position.y += p.y;
}

SDL_Point Ship::uiPosition(SDL_Point p) {
  return Map::uiPosition(p);
}
