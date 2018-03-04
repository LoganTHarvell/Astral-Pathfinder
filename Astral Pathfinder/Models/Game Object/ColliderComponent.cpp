//
//  ColliderComponent.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "ColliderComponent.hpp"

// MARK: Libraries and Frameworks
#include <iostream>
#include <cmath>

// MARK: Source Files
#include "Game.hpp"

using Vector = std::vector<SDL_Point>;


// MARK: - Constructors

ColliderComponent::ColliderComponent(SDL_Rect r) {
  center = { r.x + (r.w / 2), r.y + (r.h / 2) };
  vertices = computeVertices(center, rectVertexVectors(r), 0);
}

ColliderComponent::ColliderComponent(SDL_Point center,
                                     std::vector<SDL_Point> vertices) {
  this->center = center;
  this->vertices = vertices;
}


// MARK: - Game Loop Methods

void ColliderComponent::update(SDL_Point center, Vector vertices) {
  this->center = center;
  this->vertices = vertices;
}


// MARK: - Collider Methods

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
  // Gets axes of self and test boxes
  std::vector<std::vector<double>> axes = getAxes(0);
  auto tmp = getAxes(angle);
  axes.insert( axes.end(), tmp.begin(), tmp.end());

  // Loop axes
  for (auto axis : axes) {
    int thisMin = minAlongAxis(this->vertices, axis);
    int thisMax = maxAlongAxis(this->vertices, axis);
    int testMin = minAlongAxis(vertices, axis);
    int testMax = maxAlongAxis(vertices, axis);
    
    // No overlap along axis
    if (thisMax < testMin || thisMin > testMax) return false;
  }
  
  // Overlap on all axes
  std::cout << "Collision" << std::endl;
  return true;
}

Vector ColliderComponent::computeVertices(SDL_Point center, Vector vertexV,
                                          int angle) {
  Vector vertices;
  
  double a = angle * (M_PI / 180.0);  // degrees to radians
  
  for (auto v : vertexV) {
    // Computes new vertex vector given rotation angle
    vertices.push_back({ static_cast<int>(v.x * cos(a) + v.y * sin(a)),
                         static_cast<int>(v.x * sin(a) - v.y * cos(a)) });
    
    // Adds center point to vertex vector to compute new vertex
    vertices.back().x += center.x;
    vertices.back().y += center.y;
  }
  
  return vertices;
}

std::vector<std::vector<double>> ColliderComponent::getAxes(int angle) {
  std::vector<std::vector<double>> axes;
  axes.reserve(2 * sizeof(std::vector<std::vector<double>>));
  
  // Computes axes angle offsets in radians
  double a = angle * (M_PI / 180.0);
  double b = (angle + 90) * (M_PI / 180.0);
  
  // Computes axes vectors
  axes.push_back({ cos(a), sin(a) });
  axes.push_back({ cos(b), sin(b) });
  
  Vector normalizedAxes;
    for (auto axis : axes) {
      // Computes magnitude of axis vector
      double magnitude = sqrt(pow(axis[0], 2) + pow(axis[1], 2));
      // Normalizes axis vector
      axis = { axis[0] / magnitude, axis[1] / magnitude };
      
      // Adds 0.5 to reduce impact of rounding error during truncation
      normalizedAxes.push_back({ static_cast<int>(axis[0]+0.5),
                                 static_cast<int>(axis[1]+0.5) });
    }
  
  return axes;
}

int ColliderComponent::minAlongAxis(Vector vertices, std::vector<double> axis) {
  // Initializes min to first vertex projection along axis
  int min = (vertices[0].x * axis[0]) + (vertices[0].y * axis[1]);
  
  // Projects each vertex along axis and keeps minimum value
  for (auto v : vertices) {
    int dotProd = (v.x * axis[0]) + (v.y * axis[1]);
    if (dotProd < min) min = dotProd;
  }
  
  return min;
}

int ColliderComponent::maxAlongAxis(Vector vertices, std::vector<double> axis) {
  // Initializes max to first vertex projection along axis
  int max = (vertices[0].x * axis[0]) + (vertices[0].y * axis[1]);
  
  // Projects each vertex along axis and keeps maximum value
  for (auto v : vertices) {
    int dotProd = (v.x * axis[0]) + (v.y * axis[1]);
    if (dotProd > max) max = dotProd;
  }
  
  return max;
}


// MARK: - Helper Methods

Vector ColliderComponent::rectVertexVectors(SDL_Rect r) {
  Vector vertexVectors;
  
  // Computes rect vertices
  vertexVectors.push_back({ r.x, r.y });
  vertexVectors.push_back({ r.x + r.w, r.y });
  vertexVectors.push_back({ r.x + r.w, r.y + r.h });
  vertexVectors.push_back({ r.x, r.y + r.h });
  
  // Subtracts center point from each vertex
  SDL_Point rectCenter = { r.x + (r.w / 2), r.y + (r.h / 2) };
  for (auto& v : vertexVectors) {
    v.x -= rectCenter.x;
    v.y -= rectCenter.y;
  }
  
  return vertexVectors;
}


// MARK: - Debug Tools

void DebugTools::renderVertices(Vector vertices) {
  SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
  for (auto v : vertices) {
    SDL_RenderDrawPoint(Game::renderer, v.x, v.y);
  }
  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}
