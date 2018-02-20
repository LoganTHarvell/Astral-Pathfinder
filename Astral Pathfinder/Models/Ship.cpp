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
  velocity.x = 0;
  velocity.y = 0;
  rect.w = shipSize.w;
  rect.h = shipSize.h;

  texture = TextureManager::loadTexture("Resources/Assets/simpleSpaceship.png");
  
  rotation = 0;
  fuel = 0;
}


// MARK: - Game Loop Methods

void Ship::update() {
  // TODO: find way to pass variable in and not trigger "ship is abstract"
  updateRotation();

}

void Ship::render() {
  SDL_RenderCopyEx(Game::renderer, texture, NULL, &rect,
                   rotation, NULL, SDL_FLIP_NONE);
}


// MARK: - Ship Methods

void Ship::updateVelocity(SDL_Event e) {
  using namespace ShipParameters;
  if(e.type == SDL_KEYDOWN) {
    switch(e.key.keysym.sym) {
      case SDLK_UP:
        velocity.y = (-speed);
        break;
      case SDLK_DOWN:
        velocity.y = speed;
        break;
      case SDLK_RIGHT:
        velocity.x = speed;
        break;
      case SDLK_LEFT:
        velocity.x = (-speed);
        break;
      default:
        break;
    }
  }
  
  if(e.type == SDL_KEYUP) {
    switch(e.key.keysym.sym) {
      case SDLK_UP: case SDLK_DOWN:
        velocity.y = 0;
        break;
      case SDLK_RIGHT: case SDLK_LEFT:
        velocity.x = 0;
        break;
      default:
        break;
    }
  }
}

void Ship::move(Uint32 ticks) {
  rect.x += (velocity.x * (ticks/10));
  rect.y += (velocity.y * (ticks/10));
  
  if (checkBounds()) {
    rect.x -= (velocity.x * (ticks/10));
    rect.y -= (velocity.y * (ticks/10));
  }
}

// MARK: - Helper Methods

SDL_Point Ship::mapPosition(SDL_Point p) {
  return Map::mapPosition(p);
}

bool Ship::checkBounds() {
  return Map::checkBounds(rect);
}

void Ship::updateRotation() {
  using ShipParameters:: turnSpeed;
  
  int desiredRotation = 0;
  
  enum Quadrant {
    first = 0,
    second = 90,
    third = 180,
    fourth = 270
  };
  
  if (velocity.x && velocity.y) {
    desiredRotation = 45;
    if (velocity.x > 0 && velocity.y < 0) desiredRotation += Quadrant::first;
    if (velocity.x > 0 && velocity.y > 0) desiredRotation += Quadrant::second;
    if (velocity.x < 0 && velocity.y > 0) desiredRotation += Quadrant::third;
    if (velocity.x < 0 && velocity.y < 0) desiredRotation += Quadrant::fourth;
  }
  else if (velocity.x || velocity.y) {
    if (velocity.x) desiredRotation += (velocity.x > 0) ? 90 : 270;
    if (velocity.y) desiredRotation += (velocity.y > 0) ? 180 : 0;
  }
  else return;
  
  if (desiredRotation == rotation) return;

  int ts;
  if (desiredRotation >= Quadrant::third) {
    if (desiredRotation > rotation && rotation >= (desiredRotation+180)%360)
      ts = turnSpeed;
    else
      ts = -turnSpeed;
  }
  else {
    if (desiredRotation < rotation && rotation <= (desiredRotation+180)%360)
      ts = -turnSpeed;
    else 
      ts = turnSpeed;
  }
  
  rotation = (rotation+ts)%360;
  if (rotation < 0) rotation = rotation + 360;
}
