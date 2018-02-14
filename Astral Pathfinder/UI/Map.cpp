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



SDL_Point Map::uiPosition(SDL_Point position) {
  
  int x = GRID_X_ORIGIN + (position.x * GRID_WIDTH) + PLANET_TEXTURE_OFFSET_X;
  int y = GRID_Y_ORIGIN + (position.y * GRID_HEIGHT) + PLANET_TEXTURE_OFFSET_Y;
  
  return { x, y };
}
