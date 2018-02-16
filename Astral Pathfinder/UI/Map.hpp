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
#include "PlanetManager.hpp"
#include "Planet.hpp"


// MARK: - Map Parameters

namespace MapParameters {
  using PlanetManagerParameters::numberOfPlanets;
  using PlanetParameters::planetTexSize;
  
  const int width = 800;
  const int height = 800;
  const SDL_Point mapOrigin = { 400, 50 };
  const int gridOffset = 50;
  const SDL_Point gridOrigin = { mapOrigin.x + (gridOffset/2),
                                 mapOrigin.y + (gridOffset/2) };
  const int gridWidth = (width - gridOffset)/numberOfPlanets;
  const int gridHeight = (height - gridOffset)/numberOfPlanets;
  const SDL_Point planetTexOffset = { (gridWidth-planetTexSize)/2,
                                      (gridHeight-planetTexSize)/2 };

}


// MARK: - Map Class

class Map {
  
  struct Size {
    int w, h;
  };
  
public:
  // MARK: - Map Methods
  static SDL_Point uiPosition(SDL_Point position);
  
};

#endif /* Map_hpp */
