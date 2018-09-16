//
//  Map.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Defines functions for the Map namespace for calculating various contextual
//  information between the map and the game elements.

// MARK: Header File
#include "Map.hpp"

// MARK: Libraries and Frameworks
#include <iostream>

// MARK: Namespaces
using namespace Parameters::UI::Map;


// MARK: - Map Functions

// Calculates overall screen position for the given grid-based map coordinates
SDL_Point Map::uiPosition(SDL_Point coordinates) {
  SDL_Point planetTexOffset = { (gridWidth-planetTexSize)/2,
    (gridHeight-planetTexSize)/2};
  
  planetTexOffset.x += (rand()%planetTexOffset.x - planetTexOffset.x/2);
  planetTexOffset.y += (rand()%planetTexOffset.y - planetTexOffset.y/2);
  
  int x = gridOrigin.x + (coordinates.x * gridWidth) + planetTexOffset.x;
  int y = gridOrigin.y + (coordinates.y * gridHeight) + planetTexOffset.y;
  return { x, y };
}

// Calculates the grid-based map coordinates given an overall screen position
SDL_Point Map::mapPosition(SDL_Point uiPosition) {
  int x = uiPosition.x - rect.x;
  int y = rect.h - (uiPosition.y - rect.y);
  return { x, y };
}

// Checks if some min/max x and y screen positions are within the map
bool Map::checkBounds(SDL_Point min, SDL_Point max) {
  
  if (min.x <= rect.x) {
    std::cout << "hit left bound" << std::endl;
    return true;
  }
  if (min.y <= rect.y) {
    std::cout << "hit upper bound" << std::endl;
    return true;
  }
  if (max.x >= rect.x + rect.w) {
    std::cout << "hit right bound" << std::endl;
    return true;
  }
  if (max.y >= rect.y + rect.h) {
    std::cout << "hit lower bound" << std::endl;
    return true;
  }
  
  return false;
}
