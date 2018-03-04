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

using PointVector = std::vector<SDL_Point>;
using Axis = std::vector<double>;


// MARK: - Constructors

ColliderComponent::ColliderComponent(SDL_Rect r) {
  center = { r.x + (r.w / 2), r.y + (r.h / 2) };
  vertices = computeVertices(center, rectVertexVectors(r), 0);
}

ColliderComponent::ColliderComponent(SDL_Point center, PointVector vertices) {
  this->center = center;
  this->vertices = vertices;
}


// MARK: - Game Loop Methods

void ColliderComponent::update(SDL_Point center, PointVector vertices) {
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

bool ColliderComponent::collisionOBB(PointVector vertices, int angle) {
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

PointVector ColliderComponent::computeVertices(SDL_Point center,
                                               PointVector vertexV,
                                               int angle) {
  PointVector vertices;
  
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

std::vector<Axis> ColliderComponent::getAxes(int angle) {
  std::vector<Axis> axes;
  axes.reserve(2 * sizeof(std::vector<Axis>));
  
  // Computes axes angle offsets in radians
  double a = angle * (M_PI / 180.0);
  double b = (angle + 90) * (M_PI / 180.0);
  
  // Computes axes vectors
  axes.push_back({ cos(a), sin(a) });
  axes.push_back({ cos(b), sin(b) });
  
  return axes;
}

int ColliderComponent::minAlongAxis(PointVector vertices, Axis axis) {
  enum { x, y };  // Axis components

  // Initializes min to first vertex projection along axis
  int min = (vertices[0].x * axis[x]) + (vertices[0].y * axis[y]);
  
  // Projects each vertex along axis and keeps minimum value
  for (auto v : vertices) {
    int dotProd = (v.x * axis[x]) + (v.y * axis[y]);
    if (dotProd < min) min = dotProd;
  }
  
  return min;
}

int ColliderComponent::maxAlongAxis(PointVector vertices, Axis axis) {
  enum { x, y };  // Axis components

  // Initializes max to first vertex projection along axis
  int max = (vertices[0].x * axis[x]) + (vertices[0].y * axis[y]);
  
  // Projects each vertex along axis and keeps maximum value
  for (auto v : vertices) {
    int dotProd = (v.x * axis[x]) + (v.y * axis[y]);
    if (dotProd > max) max = dotProd;
  }
  
  return max;
}


// MARK: - Helper Methods

PointVector ColliderComponent::rectVertexVectors(SDL_Rect r) {
  PointVector vertexVectors;
  
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

void DebugTools::renderVertices(std::vector<SDL_Point> vertices) {
  SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
  for (auto v : vertices) {
    SDL_RenderDrawPoint(Game::renderer, v.x, v.y);
  }
  SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
}
