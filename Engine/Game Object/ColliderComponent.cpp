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

// MARK: Aliases
using PointVector = std::vector<SDL_Point>;


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

bool ColliderComponent::collisionCircle(int radius, PointVector vertices) {
  
  double d = 0;
  for (auto v : vertices) {
    d = sqrt((v.x-center.x)^2 + (v.y-center.y)^2);
    if (d < radius) return true;
  }
  
  return false;
}

bool ColliderComponent::collisionAABB(SDL_Rect r) {
  
  int topBound = vertices[0].y;
  int leftBound = vertices[0].x;
  int rightBound = vertices[1].x;
  int bottomBound = vertices[2].y;
  
  if (leftBound > r.x + r.w) return false;
  if (rightBound < r.x) return false;
  if (topBound > r.y + r.h) return false;
  if (bottomBound < r.y) return false;

  return true;
}

bool ColliderComponent::collisionOBB(PointVector vertices) {
  // Gets axes of self and test boxes
  PointVector axes = getNormals(this->vertices);
  std::vector<SDL_Point> tmp = getNormals(vertices);
  axes.insert(axes.end(), tmp.begin(), tmp.end());

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

int ColliderComponent::minAlongAxis(PointVector vertices, SDL_Point axis) {
  // Initializes min to first vertex projection along axis
  int min = (vertices[0].x * axis.x) + (vertices[0].y * axis.y);
  
  // Projects each vertex along axis and keeps minimum value
  for (auto v : vertices) {
    int dotProd = (v.x * axis.x) + (v.y * axis.y);
    if (dotProd < min) min = dotProd;
  }
  
  return min;
}

int ColliderComponent::maxAlongAxis(PointVector vertices, SDL_Point axis) {
  // Initializes max to first vertex projection along axis
  int max = (vertices[0].x * axis.x) + (vertices[0].y * axis.y);
  
  // Projects each vertex along axis and keeps maximum value
  for (auto v : vertices) {
    int dotProd = (v.x * axis.x) + (v.y * axis.y);
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

PointVector ColliderComponent::getNormals(PointVector vertices) {
  PointVector normals;
  
  for (int i = 1; i < vertices.size()-1; i++) {
    normals.push_back({ vertices[i + 1].x - vertices[i].x,
                        -(vertices[i + 1].y - vertices[i].y) });
  }
  
  normals.push_back({ vertices[1].x - vertices[vertices.size()-1].x,
                      -(vertices[1].y - vertices[vertices.size()-1].y) });
  
  return normals;
}


// MARK: - Debug Tools

void DebugTools::renderVertices(std::vector<SDL_Point> vertices,
                                SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (auto v : vertices) {
    SDL_RenderDrawPoint(renderer, v.x, v.y);
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
