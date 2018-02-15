//
//  Map.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "parameters.h"

class Map {
  
  struct Coordinates {
    float x,y;
  };
  
  struct Size {
    int w, h;
  };
  
public:
  // MARK: - Map Constants
  static const int mapWidth = 800;
  static const int mapHeight = 800;
  static constexpr Coordinates mapOrigin = { 400, 50 };
  static const int gridOffset = 50;
  static constexpr Coordinates gridOrigin = { mapOrigin.x + (gridOffset/2.0),
                                              mapOrigin.y + (gridOffset/2.0) };
  static constexpr float gridWidth = (mapWidth - gridOffset)/NUMBER_OF_PLANETS;
  static constexpr float gridHeight = (mapHeight - gridOffset)/NUMBER_OF_PLANETS;
  static const int planetTexSize = 8;
  static constexpr Coordinates planetTexOffset = { (gridWidth-planetTexSize)/2,
                                                   (gridHeight-planetTexSize)/2 };
  
  
  // MARK: - Map Methods
  static SDL_Point uiPosition(SDL_Point position);
  
};

#endif /* Map_hpp */
