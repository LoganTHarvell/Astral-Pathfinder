//
//  AlienShip.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 4/29/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#include "AlienShip.hpp"

#include "TextureManager.hpp"

using PointVector = std::vector<SDL_Point>;


// MARK: - Initialization Methods

void AlienShip::init(SDL_Point startPosition) {
  using namespace ShipParameters;
  
  tag = playerShip;
  
  velocity.x = 0;
  velocity.y = 0;
  
  rotation = 270;
  
  rect.x = startPosition.x;
  rect.y = startPosition.y;
  rect.w = shipSize.w;
  rect.h = shipSize.h;
  
  collider = new ColliderComponent(getCenter(), computeShipVertices());
  texture = TextureManager::loadTexture(movingPlayerTex);
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
 
  auto *keyState = SDL_GetKeyboardState(NULL);
  
  if (keyState[SDL_SCANCODE_UP]) velocity.y = (-speed);
  else if (keyState[SDL_SCANCODE_DOWN]) velocity.y = speed;
  else velocity.y = 0;
  
  if (keyState[SDL_SCANCODE_RIGHT]) velocity.x = speed;
  else if (keyState[SDL_SCANCODE_LEFT]) velocity.x = (-speed);
  else velocity.x = 0;
}
