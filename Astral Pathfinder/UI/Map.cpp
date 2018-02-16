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


// MARK: - Map Methods

SDL_Point Map::uiPosition(SDL_Point p) {
  int x = gridOrigin.x + (p.x * gridWidth) + planetTexOffset.x;
  int y = gridOrigin.y + (p.y * gridHeight) + planetTexOffset.y;
  return { x, y };
}

SDL_Point Map::mapPosition(SDL_Point p) {
  int x = p.x - mapOrigin.x;
  int y = p.x - mapOrigin.y;
  return { x, y };
}

bool Map::checkBounds(SDL_Rect r) {
  
  if (r.x <= mapOrigin.x) {
    std::cout << "Hit left bound" << std::endl;
    return true;
  }
  if (r.y <= mapOrigin.y) {
    std::cout << "Hit upper bound" << std::endl;
    return true;
  }
  if (r.x + r.w >= mapOrigin.x + width) {
    std::cout << "Hit right bound" << std::endl;
    return true;
  }
  if (r.y + r.h >= mapOrigin.y + height) {
    std::cout << "Hit lower bound" << std::endl;
    return true;
  }
  
  return false;
}
