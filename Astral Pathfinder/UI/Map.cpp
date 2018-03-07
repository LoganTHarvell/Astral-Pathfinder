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

SDL_Point Map::uiPosition(SDL_Point coordinates) {
  int x = gridOrigin.x + (coordinates.x * gridWidth) + planetTexOffset.x;
  int y = gridOrigin.y + (coordinates.y * gridHeight) + planetTexOffset.y;
  return { x, y };
}

SDL_Point Map::mapPosition(SDL_Point uiPosition) {
  int x = uiPosition.x - mapOrigin.x;
  int y = uiPosition.x - mapOrigin.y;
  return { x, y };
}

bool Map::checkBounds(SDL_Point min, SDL_Point max) {
  
  if (min.x <= mapOrigin.x) {
    std::cout << "Hit left bound" << std::endl;
    return true;
  }
  if (min.y <= mapOrigin.y) {
    std::cout << "Hit upper bound" << std::endl;
    return true;
  }
  if (max.x >= mapOrigin.x + width) {
    std::cout << "Hit right bound" << std::endl;
    return true;
  }
  if (max.y >= mapOrigin.y + height) {
    std::cout << "Hit lower bound" << std::endl;
    return true;
  }
  
  return false;
}
