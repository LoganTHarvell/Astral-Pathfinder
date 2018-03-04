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
  
  rotation = 270;
  
  auto shipVertices = ColliderComponent::computeVertices(getCenter(),
                                                         shipVertexVectors(),
                                                         rotation);
  collider = new ColliderComponent(getCenter(), shipVertices);

  texture = TextureManager::loadTexture("Resources/Assets/movingPlayerShip.png");
  
  fuel = 0;
}


// MARK: - Game Loop Methods

void Ship::update() {
  updateVelocity();
  updateRotation();
  
  auto shipVertices = ColliderComponent::computeVertices(getCenter(),
                                                         shipVertexVectors(),
                                                         rotation);
  collider->update(getCenter(), shipVertices);
}

void Ship::render() {

  // MARK: DEBUG ONLY
  auto shipVertices = collider->getVertices();
  SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
  for (auto v : shipVertices) {
    SDL_RenderDrawPoint(Game::renderer, v.x, v.y);
  }
  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);

  SDL_RenderCopyEx(Game::renderer, texture, NULL, &rect,
                   rotation, NULL, SDL_FLIP_NONE);
}


// MARK: - Ship Methods

void Ship::updateVelocity() {
  using namespace ShipParameters;
  
  auto *keyState = SDL_GetKeyboardState(NULL);
  
  if (keyState[SDL_SCANCODE_UP]) velocity.y = (-speed);
  else if (keyState[SDL_SCANCODE_DOWN]) velocity.y = speed;
  else velocity.y = 0;
  
  if (keyState[SDL_SCANCODE_RIGHT]) velocity.x = speed;
  else if (keyState[SDL_SCANCODE_LEFT]) velocity.x = (-speed);
  else velocity.x = 0;
  
}

void Ship::move(Uint32 ticks) {
  rect.x += (velocity.x * (ticks/10));
  rect.y += (velocity.y * (ticks/10));
  
  if (boundaryCollision()) {
    rect.x -= (velocity.x * (ticks/10));
    rect.y -= (velocity.y * (ticks/10));
  }
}

// MARK: - Helper Methods

SDL_Point Ship::mapPosition(SDL_Point p) {
  return Map::mapPosition(p);
}

bool Ship::boundaryCollision() {
  auto vertexV = shipVertexVectors();
  auto vertices = collider->computeVertices(getCenter(), vertexV, rotation);
  auto axes = collider->getAxes(0);
  
  SDL_Point mins = { collider->minAlongAxis(vertices, axes[0]),
                    collider->minAlongAxis(vertices, axes[1]) };
  SDL_Point maxs = { collider->maxAlongAxis(vertices, axes[0]),
                    collider->maxAlongAxis(vertices, axes[1]) };
  
  return Map::checkBounds(mins, maxs);
}

std::vector<SDL_Point> Ship::shipVertexVectors() {
  std::vector<SDL_Point> cornerVectors;
  
  cornerVectors.push_back({ rect.x, rect.y + rect.h/2 });
  cornerVectors.push_back({ rect.x + rect.w/2, rect.y });
  cornerVectors.push_back({ rect.x + rect.w, rect.y + rect.h/2 });
  cornerVectors.push_back({ rect.x + rect.w/2, rect.y + rect.h });
  
  SDL_Point center = getCenter();
  for (auto& cv : cornerVectors) {
    cv.x -= center.x;
    cv.y -= center.y;
  }
  
  return cornerVectors;
}


void Ship::updateRotation() {
  using ShipParameters:: turnSpeed;
  
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
