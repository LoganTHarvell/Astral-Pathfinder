//
//  PlayerShip.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 4/29/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//
//  Description:
//  Class extension of Ship base class for modeling the player. Handles input
//  based movement to calculate velocity vectors, calculating vertex vectors.
//  Also handles initializing and updating.

// MARK: Header File
#include "PlayerShip.hpp"

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "TextureManager.hpp"

// MARK: Aliases
using PointVector = std::vector<SDL_Point>;


// MARK: - Initialization Methods

void PlayerShip::init(SDL_Point startPosition) {
  using namespace Parameters::Ship;
  
  tag = Ship::playerShip;
  crewPopulation = shipPopulation;
  fuel = 0;
  
  velocity.x = 0;
  velocity.y = 0;
  
  rotation = 270;
  
  rect.x = startPosition.x;
  rect.y = startPosition.y;
  rect.w = Parameters::Ship::shipRect.w;
  rect.h = Parameters::Ship::shipRect.h;
  
  collider = new ColliderComponent(getCenter(), computeShipVertices());
  TextureManager::loadTexture(playerTexFile, &texture, Game::renderer);
}


void PlayerShip::update(Game::State * gs) {
  
  // Base class update methods
  updateVelocity();
  updateRotation();
  updatePosition(gs->ticks);
  collider->update(getCenter(), computeShipVertices());
}

// Calculates vertex vectors, the vectors from the center to the vertices
PointVector PlayerShip::shipVertexVectors() {
  PointVector cornerVectors;
  
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

void PlayerShip::updateVelocity() {
  using namespace Parameters::Ship;

  // Prevents movement without fuel
  if (fuel <= 0) {
    velocity.x = velocity.y = 0;
    return;
  }
  
  auto *keyState = SDL_GetKeyboardState(NULL);
  
  // Sets velocity components based on keyboard inputs
  if (keyState[SDL_SCANCODE_UP]) velocity.y = (-speed);
  else if (keyState[SDL_SCANCODE_DOWN]) velocity.y = speed;
  else velocity.y = 0;
  
  if (keyState[SDL_SCANCODE_RIGHT]) velocity.x = speed;
  else if (keyState[SDL_SCANCODE_LEFT]) velocity.x = (-speed);
  else velocity.x = 0;
  
  // Decreases fuel during movement
  if (velocity.x != 0 || velocity.y != 0) fuel -=1;
}

// Refuels ship with given mineral amount
void PlayerShip::updateFuel(int minerals) {
  fuel += minerals;
}
