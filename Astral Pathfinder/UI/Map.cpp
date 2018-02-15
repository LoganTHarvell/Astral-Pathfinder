//
//  Map.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Map.hpp"


// MARK: - Map Constants
const int Map::mapWidth = 800;
const int Map::mapHeight = 800;
const SDL_Point Map::mapOrigin = { 400, 50 };
const int Map::gridOffset = 50;
const SDL_Point Map::gridOrigin = { mapOrigin.x + (gridOffset/2),
  mapOrigin.y + (gridOffset/2) };
const int Map::gridWidth = (mapWidth - gridOffset)/NUMBER_OF_PLANETS;
const int Map::gridHeight = (mapHeight - gridOffset)/NUMBER_OF_PLANETS;
const int Map::planetTexSize = 8;
const SDL_Point Map::planetTexOffset = { (gridWidth-planetTexSize)/2,
                                         (gridHeight-planetTexSize)/2 };


// MARK: - Map Methods

SDL_Point Map::uiPosition(SDL_Point position) {
  
  int x = gridOrigin.x + (position.x * gridWidth) + planetTexOffset.x;
  int y = gridOrigin.y + (position.y * gridHeight) + planetTexOffset.y;
  
  return { x, y };
}
