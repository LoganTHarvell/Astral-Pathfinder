//
//  Map.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Map.hpp"

// MARK: Source Files
#include "Planet.hpp"


// MARK: - Map Methods

SDL_Point Map::uiPosition(SDL_Point position) {
  using namespace MapParameters;

  int x = gridOrigin.x + (position.x * gridWidth) + planetTexOffset.x;
  int y = gridOrigin.y + (position.y * gridHeight) + planetTexOffset.y;
  
  return { x, y };
}

