//
//  AlienShip.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 4/29/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#include "AlienShip.hpp"

#include <cmath>

#include "TextureManager.hpp"

using PointVector = std::vector<SDL_Point>;


// MARK: - Initialization Methods

void AlienShip::init(SDL_Point startPosition) {
  using namespace ShipParameters;
  
  tag = alienWarship;
  
  velocity.x = 0;
  velocity.y = 0;
  
  rotation = 270;
  
  rect.x = startPosition.x;
  rect.y = startPosition.y;
  rect.w = shipSize.w;
  rect.h = shipSize.h;
  
  setMainTarget(getCenter());
  resetTarget();
  
  collider = new ColliderComponent(getCenter(), computeShipVertices());
  texture = TextureManager::loadTexture(alienTex);
}


void AlienShip::update(Game::State * gs) {
  updateVelocity();
  updateRotation();
  
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

void AlienShip::updateTarget(SDL_Point p) {
  target = mainTarget;
  
  SDL_Point center = getCenter();
  double dMain = sqrt((target.x-center.x)^2 + (target.y-center.y)^2);
  double dTest = sqrt((p.x-center.x)^2 + (p.y-center.y)^2);
  
  if (dTest < dMain) target = p;
}

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

void AlienShip::updateVelocity() {
  using namespace ShipParameters;
 
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
