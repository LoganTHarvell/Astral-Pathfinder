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
  SDL_SetTextureColorMod(texture, 200, 0, 0);
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
 
  int xdir = target.x - rect.x ;
  int ydir = target.y - rect.y;
  
  if (xdir > 0) velocity.x = speed;
  else if (xdir < 0) velocity.x = -speed;
  else velocity.x = 0;
  
  if (ydir > 0) velocity.y = speed;
  else if (ydir < 0) velocity.y = -speed;
  else velocity.y = 0;
}
