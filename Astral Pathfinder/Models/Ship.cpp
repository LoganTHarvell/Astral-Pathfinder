//
//  Ship.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Ship.hpp"

// MARK: Libraries and Frameworks
#include <iostream>

// MARK: Source Files
#include "Game.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"


// MARK: - Initialization Methods

void Ship::init(SDL_Point p) {
  using namespace ShipParameters;
  
  rect.x = p.x;
  rect.y = p.y;
  xVel = 0;
  yVel = 0;
  rect.w = shipSize.w;
  rect.h = shipSize.h;

  texture = TextureManager::loadTexture("Resources/Assets/simpleSpaceship.png");
  
  rotation = 0;
  fuel = 0;
}


// MARK: - Game Loop Methods

void Ship::update() {
  // TODO: find way to pass variable in and not trigger "ship is abstract"
}

void Ship::render() {
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}


// MARK: - Ship Methods


void Ship::updateVelocity(SDL_Event e) {
  using namespace ShipParameters;
  if(e.type == SDL_KEYDOWN) {
    switch(e.key.keysym.sym) {
      case SDLK_UP:
        yVel = (-velocity);
        break;
      case SDLK_DOWN:
        yVel = velocity;
        break;
      case SDLK_RIGHT:
        xVel = velocity;
        break;
      case SDLK_LEFT:
        xVel = (-velocity);
        break;
      default:
        break;
    }
  }
  
  if(e.type == SDL_KEYUP) {
    switch(e.key.keysym.sym) {
      case SDLK_UP:
        yVel = 0;
        break;
      case SDLK_DOWN:
        yVel = 0;
        break;
      case SDLK_RIGHT:
        xVel = 0;
        break;
      case SDLK_LEFT:
        xVel = 0;
        break;
      default:
        break;
    }
  }
}

void Ship::move(Uint32 ticks) {
  
  rect.x += (xVel * (ticks/10));
  rect.y += (yVel * (ticks/10));
  
/*  if (checkBounds()) {
    rect.x -= p.x;
    rect.y -= p.y;
  }  to be fixed */
}

// MARK: - Helper Methods

SDL_Point Ship::mapPosition(SDL_Point p) {
  return Map::mapPosition(p);
}

bool Ship::checkBounds() {
  return Map::checkBounds(rect);
}
