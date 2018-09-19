//
//  Ship.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Abstract class extension of GameObject used as a base class to model Ship
//  game elements. Handles ship bounding box position and orientation, as well
//  as boundary collisions using the collider component. Also handles rendering.

// MARK: Header File
#include "Ship.hpp"

// MARK: Libraries and Frameworks
#include <iostream>

// MARK: Source Files
#include "Map.hpp"

// MARK: Aliases
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

// Computes ship bounding vertices
PointVector Ship::computeShipVertices() {
  
  SDL_Point c = getCenter();
  PointVector svv = shipVertexVectors();
  int r = rotation;
  PointVector shipVertices = ColliderComponent::computeVertices(c, svv, r);

  return shipVertices;

}

// Updates the facing direction of the ship over time, based on velocity vector
void Ship::updateRotation() {
  using Parameters::Ship:: turnSpeed;
  
  int desiredRotation = 0;
  
  // Enum for angles
  enum Direction {
    right = 0, downRight = 45,
    down = 90, downLeft = 135,
    left = 180, upLeft = 225,
    up = 270, upRight = 315
  };
  
  // Determines 8-directional desired direction based on velocity vectors
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

  // Sets turning direction according to smallest radial distance of turn
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
  
  // Maintains rotation angle between 0 and 360
  int tmp = rotation;
  rotation = (rotation+ts)%360;
  if (rotation < 0) rotation = rotation + 360;
  
  // Prevents rotation past boundary
  if (boundaryCollision()) {
    rotation = tmp;
  }
  
}

// Updates position with velocity in respect to time
void Ship::updatePosition(Uint32 ticks) {
  rect.x += (velocity.x * (ticks/10));
  rect.y += (velocity.y * (ticks/10));
  
  if (boundaryCollision()) {
    rect.x -= (velocity.x * (ticks/10));
    rect.y -= (velocity.y * (ticks/10));
  }
}
