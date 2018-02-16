//
//  Map.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Map.hpp"

// MARK: Libraries and Frameworks
#include <iostream>

// MARK: Source Files
#include "Planet.hpp"


using namespace Map::Functions;
using namespace Map::Parameters;

// MARK: - Map Methods

SDL_Point uiPosition(SDL_Point p) {
  int x = gridOrigin.x + (p.x * gridWidth) + planetTexOffset.x;
  int y = gridOrigin.y + (p.y * gridHeight) + planetTexOffset.y;
  return { x, y };
}

SDL_Point mapPosition(SDL_Point p) {
  int x = p.x - mapOrigin.x;
  int y = p.x - mapOrigin.y;
  return { x, y };
}

bool checkBounds(SDL_Rect r) {
  
  if (r.x <= mapOrigin.x) {
    return true;
  }
  if (r.y <= mapOrigin.y) {
    return true;
  }
  if (r.x + r.w >= mapOrigin.x + width) {
    return true;
  }
  if (r.y + r.h >= mapOrigin.y + height) {
    return true;
  }
  
  std::cout << "Hit Bounds" << std::endl;
  
  return false;
}
