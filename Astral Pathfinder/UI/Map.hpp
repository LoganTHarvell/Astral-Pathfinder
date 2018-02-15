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
  
  struct Size {
    int w, h;
  };
  
public:
  // MARK: - Map Methods
  static SDL_Point uiPosition(SDL_Point position);
  
private:
  // MARK: - Map Private Constants
  static const int mapWidth;
  static const int mapHeight;
  static const SDL_Point mapOrigin;
  static const int gridOffset;
  static const SDL_Point gridOrigin;
  static const int gridWidth;
  static const int gridHeight;
  static const SDL_Point planetTexOffset;
  
};

#endif /* Map_hpp */
