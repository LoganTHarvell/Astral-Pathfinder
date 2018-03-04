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
}

ColliderComponent::ColliderComponent(SDL_Point center,
                                     std::vector<SDL_Point> vertices) {
  this->center = center;
  this->vertices = vertices;
}


void ColliderComponent::update(SDL_Point center, Vector vertices) {
  this->center = center;
  this->vertices = vertices;
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

bool ColliderComponent::collisionOBB(Vector vertices, int angle) {
  std::vector<std::vector<double>> axes = getAxes(0);
  auto tmp = getAxes(angle);
  axes.insert( axes.end(), tmp.begin(), tmp.end());

  for (auto axis : axes) {
    int thisMin = minAlongAxis(this->vertices, axis);
    int thisMax = maxAlongAxis(this->vertices, axis);
    int testMin = minAlongAxis(vertices, axis);
    int testMax = maxAlongAxis(vertices, axis);
    
    if (thisMax < testMin || thisMin > testMax) return false;
  }
  
  std::cout << "Collision" << std::endl;
  return true;
}


int ColliderComponent::minAlongAxis(Vector corners, std::vector<double> axis) {
  int min = (corners[0].x * axis[0]) + (corners[0].y * axis[1]);
  
  for (auto c : corners) {
    int dotProd = (c.x * axis[0]) + (c.y * axis[1]);
    if (dotProd < min) min = dotProd;
  }
  
  return min;
}

int ColliderComponent::maxAlongAxis(Vector corners, std::vector<double> axis) {
  int max = (corners[0].x * axis[0]) + (corners[0].y * axis[1]);
  
  for (auto c : corners) {
    int dotProd = (c.x * axis[0]) + (c.y * axis[1]);
    if (dotProd > max) max = dotProd;
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

std::vector<std::vector<double>> ColliderComponent::getAxes(int angle) {
  std::vector<std::vector<double>> axes;
  axes.reserve(2 * sizeof(std::vector<std::vector<double>>));
  
  double a = angle * (M_PI / 180.0);
  double b = (angle + 90) * (M_PI / 180.0);

  axes.push_back({ cos(a), sin(a) });
  axes.push_back({ cos(b), sin(b) });
  
  std::vector<std::vector<double>> normalizedAxes = axes;
//  for (auto axis : axes) {
//    double magnitude = sqrt(pow(axis[0], 2) + pow(axis[1], 2));
//    axis = { axis[0] / magnitude, axis[1] / magnitude };
//    normalizedAxes.push_back({ static_cast<int>(axis[0]),
//                               static_cast<int>(axis[1]) });
//  }
  
  return normalizedAxes;
}
