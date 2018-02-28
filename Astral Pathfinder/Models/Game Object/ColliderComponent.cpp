//
//  ColliderComponent.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "ColliderComponent.hpp"

#include <iostream>
#include <cmath>


ColliderComponent::ColliderComponent(SDL_Rect r) {
  rect = r;
}


bool ColliderComponent::collisionAABB(SDL_Rect r) {
  if (rect.x > r.x + r.w) {
    return false;
  }
  if (rect.x + rect.w < r.x) {
    return false;
  }
  if (rect.y > r.y + r.h) {
    return false;
  }
  if (rect.y + rect.h < r.y) {
    return false;
  }
  
  std::cout << "Collision" << std::endl;
  return true;
}

bool ColliderComponent::collisionOBB(SDL_Rect r, int angle) {
  SDL_Point min = minAlongXY(shipVertices(r, angle));
  SDL_Point max = maxAlongXY(shipVertices(r, angle));
  
  if (rect.x + rect.w < min.x || rect.x > max.x) return false;
  if (rect.y + rect.h < min.y || rect.y > max.y) return false;
    
  std::cout << "Collision" << std::endl;
  return true;
  
  return true;
}


SDL_Point ColliderComponent::minAlongXY(std::vector<SDL_Point> corners) {
  SDL_Point min = corners.front();
  
  for (auto c : corners) {
    if (c.x < min.x) min.x = c.x;
    if (c.y < min.y) min.y = c.y;
  }
  
  return min;
}

SDL_Point ColliderComponent::maxAlongXY(std::vector<SDL_Point> corners) {
  SDL_Point max = corners.front();
  
  for (auto c : corners) {
    if (c.x > max.x) max.x = c.x;
    if (c.y > max.y) max.y = c.y;
  }
  
  return max;
}

std::vector<SDL_Point> ColliderComponent::shipVertices(SDL_Rect r, int angle) {
  std::vector<SDL_Point> corners;
  
  SDL_Point center = { r.x + (r.w / 2), r.y + (r.h / 2) };
  double a = angle * (M_PI / 180.0);
  
  std::vector<SDL_Point> cv = shipVertexVectors(r);
  for (auto& v : cv) {
    corners.push_back({ static_cast<int>(v.x * cos(a) + v.y * sin(a)),
                        static_cast<int>(v.x * sin(a) - v.y * cos(a)) });
    
    corners.back().x += center.x;
    corners.back().y += center.y;
  }
  
  return corners;
}

std::vector<SDL_Point> ColliderComponent::shipVertexVectors(SDL_Rect r) {
  std::vector<SDL_Point> cornerVectors;
  
  cornerVectors.push_back({ r.x, r.y + r.h/2 });
  cornerVectors.push_back({ r.x + r.w/2, r.y });
  cornerVectors.push_back({ r.x + r.w, r.y + r.h/2 });
  cornerVectors.push_back({ r.x + r.w/2, r.y + r.h/2 });
  
  SDL_Point center = { r.x + (r.w / 2), r.y + (r.h / 2) };
  for (auto& cv : cornerVectors) {
    cv.x -= center.x;
    cv.y -= center.y;
  }
  
  return cornerVectors;
}
