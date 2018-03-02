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

using Vector = std::vector<SDL_Point>;

ColliderComponent::ColliderComponent(SDL_Rect r) {
  center = { r.x + (r.w / 2), r.y + (r.h / 2) };
  vertices = computeVertices(center, rectVertexVectors(r), 0);
  min = minAlongXY(vertices);
  max = maxAlongXY(vertices);
}

ColliderComponent::ColliderComponent(SDL_Point center,
                                     std::vector<SDL_Point> vertices) {
  this->center = center;
  this->vertices = vertices;
  min = minAlongXY(vertices);
  max = maxAlongXY(vertices);
}


void ColliderComponent::update(SDL_Point center, Vector vertices) {
  this->center = center;
  this->vertices = vertices;
  min = minAlongXY(vertices);
  max = maxAlongXY(vertices);
}

// MARK: - Collision Methods

bool ColliderComponent::collisionAABB(SDL_Rect r) {
  
  int topBound = vertices[0].y;
  int leftBound = vertices[0].x;
  int rightBound = vertices[1].x;
  int bottomBound = vertices[2].y;
  
  if (leftBound > r.x + r.w) return false;
  if (rightBound < r.x) return false;
  if (topBound > r.y + r.h) return false;
  if (bottomBound < r.y) return false;

  std::cout << "Collision" << std::endl;
  return true;
}

bool ColliderComponent::collisionOBB(Vector vertices) {
  SDL_Point min = minAlongXY(vertices);
  SDL_Point max = maxAlongXY(vertices);
  
  if (this->max.x < min.x || this->min.x > max.x) return false;
  if (this->max.y < min.y || this->min.y > max.y) return false;
    
  std::cout << "Collision" << std::endl;
  
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

SDL_Point ColliderComponent::maxAlongXY(Vector corners) {
  SDL_Point max = corners.front();
  
  for (auto c : corners) {
    if (c.x > max.x) max.x = c.x;
    if (c.y > max.y) max.y = c.y;
  }
  
  return max;
}

Vector ColliderComponent::computeVertices(SDL_Point center, Vector vertexV,
                                          int angle) {
  Vector vertices;
  
  double a = angle * (M_PI / 180.0);
  
  for (auto v : vertexV) {
    vertices.push_back({ static_cast<int>(v.x * cos(a) + v.y * sin(a)),
                         static_cast<int>(v.x * sin(a) - v.y * cos(a)) });
    
    vertices.back().x += center.x;
    vertices.back().y += center.y;
  }
  
  return vertices;
}

Vector ColliderComponent::rectVertexVectors(SDL_Rect r) {
  Vector cornerVectors;
  
  cornerVectors.push_back({ r.x, r.y });
  cornerVectors.push_back({ r.x + r.w, r.y });
  cornerVectors.push_back({ r.x + r.w, r.y + r.h });
  cornerVectors.push_back({ r.x, r.y + r.h });
  
  for (auto& cv : cornerVectors) {
    cv.x -= center.x;
    cv.y -= center.y;
  }
  
  return cornerVectors;
}
