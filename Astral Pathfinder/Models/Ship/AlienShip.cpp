//
//  AlienShip.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 4/29/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//
//  Description:
//  Class extension of Ship base class for modeling an AI enemy. Handles path
//  planning and velocity calculations, as well as calculating vertex vectors.
//  Also handles initializing and updating.

// MARK: Header File
#include "AlienShip.hpp"

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "TextureManager.hpp"
#include <cmath>

// MARK: Aliases
using PointVector = std::vector<SDL_Point>;


// MARK: - Initialization Methods

void AlienShip::init(SDL_Point startPosition) {
  using namespace Parameters::Ship;
  
  tag = Ship::alienWarship;
  
  velocity.x = 0;
  velocity.y = 0;
  
  rotation = 270;
  
  rect.x = startPosition.x;
  rect.y = startPosition.y;
  rect.w = Parameters::Ship::shipRect.w;
  rect.h = Parameters::Ship::shipRect.h;
  
  setMainTarget(getCenter());
  resetTarget();
  
  collider = new ColliderComponent(getCenter(), computeShipVertices());
  TextureManager::loadTexture(alienTexFile, &texture, Game::renderer);
}


void AlienShip::update(Game::State * gs) {
  
  // Base class update methods
  updateVelocity();
  updateRotation();
  
  // Updates position every other frame
  if (gs->frame%2 == 0) {
    updatePosition(gs->ticks);
  }
  
  collider->update(getCenter(), computeShipVertices());
}

void AlienShip::setMainTarget(SDL_Point p) {
  mainTarget = p;
}

void AlienShip::resetTarget() {
  target = mainTarget;
}

// TODO: work in progress
// Sets a temporary target to point, if point is closer than main target
void AlienShip::updateTarget(SDL_Point p) {
  target = mainTarget;
  
  SDL_Point center = getCenter();
  double dMain = sqrt((target.x-center.x)^2 + (target.y-center.y)^2);
  double dTest = sqrt((p.x-center.x)^2 + (p.y-center.y)^2);
  
  if (dTest < dMain) target = p;
}

// Calculates vertex vectors, the vectors from the center to the vertices
PointVector AlienShip::shipVertexVectors() {
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

// Updates velocity components based on vector to target
void AlienShip::updateVelocity() {
  using namespace Parameters::Ship;
 
  SDL_Point center = getCenter();
  
  int xdir = target.x - center.x ;
  int ydir = target.y - center.y;
  
  if (xdir > 0) velocity.x = speed;
  else if (xdir < 0) velocity.x = -speed;
  else velocity.x = 0;
  
  if (ydir > 0) velocity.y = speed;
  else if (ydir < 0) velocity.y = -speed;
  else velocity.y = 0;
}
