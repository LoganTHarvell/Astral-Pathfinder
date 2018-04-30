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
  SDL_Point planetTexOffset = { (gridWidth-planetTexSize)/2,
    (gridHeight-planetTexSize)/2};
  
  planetTexOffset.x += (rand()%planetTexOffset.x - planetTexOffset.x/2);
  planetTexOffset.y += (rand()%planetTexOffset.y - planetTexOffset.y/2);
  
  int x = gridOrigin.x + (coordinates.x * gridWidth) + planetTexOffset.x;
  int y = gridOrigin.y + (coordinates.y * gridHeight) + planetTexOffset.y;
  return { x, y };
}

SDL_Point Map::mapPosition(SDL_Point uiPosition) {
  int x = uiPosition.x - mapOrigin.x;
  int y = height - (uiPosition.y - mapOrigin.y);
  return { x, y };
}

bool Map::checkBounds(SDL_Point min, SDL_Point max) {
  
  if (min.x <= mapOrigin.x) {
    std::cout << "hit left bound" << std::endl;
    return true;
  }
  if (min.y <= mapOrigin.y) {
    std::cout << "hit upper bound" << std::endl;
    return true;
  }
  if (max.x >= mapOrigin.x + width) {
    std::cout << "hit right bound" << std::endl;
    return true;
  }
  if (max.y >= mapOrigin.y + height) {
    std::cout << "hit lower bound" << std::endl;
    return true;
  }
  
  return false;
}
