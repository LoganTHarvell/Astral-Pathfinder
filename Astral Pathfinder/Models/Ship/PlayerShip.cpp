//
//  PlayerShip.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 4/29/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

// MARK: Header File
#include "PlayerShip.hpp"

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "TextureManager.hpp"

using PointVector = std::vector<SDL_Point>;


// MARK: - Initialization Methods

void PlayerShip::init(SDL_Point startPosition) {
  using namespace Parameters::Ship;
  
  tag = Ship::playerShip;
  crewPopulation = totalCrew;
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
  updateVelocity();
  updateRotation();
  updatePosition(gs->ticks);
  
  collider->update(getCenter(), computeShipVertices());
}


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
  
  if (fuel <= 0) {
    velocity.x = velocity.y = 0;
    return;
  }
  
  auto *keyState = SDL_GetKeyboardState(NULL);
  
  if (keyState[SDL_SCANCODE_UP]) velocity.y = (-speed);
  else if (keyState[SDL_SCANCODE_DOWN]) velocity.y = speed;
  else velocity.y = 0;
  
  if (keyState[SDL_SCANCODE_RIGHT]) velocity.x = speed;
  else if (keyState[SDL_SCANCODE_LEFT]) velocity.x = (-speed);
  else velocity.x = 0;
  
  if (velocity.x != 0 || velocity.y != 0) fuel -=1;
}

void PlayerShip::updateFuel(int minerals) {
  fuel += minerals;
}
