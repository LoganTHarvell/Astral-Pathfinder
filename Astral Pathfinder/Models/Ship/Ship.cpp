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


using PointVector = std::vector<SDL_Point>;


// MARK: - Game Loop Methods

void Ship::render(Game::State *gs) {
  SDL_RenderCopyEx(Game::renderer, texture, NULL, &rect,
                   rotation, NULL, SDL_FLIP_NONE);
}


// MARK: - Ship Methods

SDL_Point Ship::mapPosition() {
  return Map::mapPosition(getCenter());
}


// MARK: - Helper Methods

bool Ship::boundaryCollision() {
  PointVector vertices = computeShipVertices();
  
  PointVector axes;
  axes.push_back({ 1, 0 });   // X axis normal vector
  axes.push_back({ 0, 1 });   // Y axis normal vector
  
  SDL_Point mins = { collider->minAlongAxis(vertices, axes[0]),
                     collider->minAlongAxis(vertices, axes[1]) };
  SDL_Point maxs = { collider->maxAlongAxis(vertices, axes[0]),
                     collider->maxAlongAxis(vertices, axes[1]) };
  
  return Map::checkBounds(mins, maxs);
}

PointVector Ship::computeShipVertices() {
  SDL_Point c = getCenter();
  PointVector svv = shipVertexVectors();
  int r = rotation;
  PointVector shipVertices = ColliderComponent::computeVertices(c, svv, r);
  return shipVertices;
}

void Ship::updateRotation() {
  using Parameters::Ship:: turnSpeed;
  
  int desiredRotation = 0;
  
  enum Direction {
    right = 0, downRight = 45,
    down = 90, downLeft = 135,
    left = 180, upLeft = 225,
    up = 270, upRight = 315
  };
  
  if (velocity.x == 0 && velocity.y == 0) return;
  if (velocity.x > 0 && velocity.y == 0) desiredRotation = Direction::right;
  if (velocity.x > 0 && velocity.y > 0) desiredRotation = Direction::downRight;
  if (velocity.x == 0 && velocity.y > 0) desiredRotation = Direction::down;
  if (velocity.x < 0 && velocity.y > 0) desiredRotation = Direction::downLeft;
  if (velocity.x < 0 && velocity.y == 0) desiredRotation = Direction::left;
  if (velocity.x < 0 && velocity.y < 0) desiredRotation = Direction::upLeft;
  if (velocity.x == 0 && velocity.y < 0) desiredRotation = Direction::up;
  if (velocity.x > 0 && velocity.y < 0) desiredRotation = Direction::upRight;


  if (desiredRotation == rotation) return;

  int ts;
  if (desiredRotation >= 180) {
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
  
  int tmp = rotation;
  rotation = (rotation+ts)%360;
  if (rotation < 0) rotation = rotation + 360;
  
  if (boundaryCollision()) {
    rotation = tmp;
  }
  
}

void Ship::updatePosition(Uint32 ticks) {
  rect.x += (velocity.x * (ticks/10));
  rect.y += (velocity.y * (ticks/10));
  
  if (boundaryCollision()) {
    rect.x -= (velocity.x * (ticks/10));
    rect.y -= (velocity.y * (ticks/10));
  }
}
