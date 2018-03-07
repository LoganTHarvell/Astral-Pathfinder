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


namespace Map {
  using PlanetManagerParameters::numberOfPlanets;
  using PlanetParameters::planetTexSize;
  
  
  // MARK: - Map Parameters
  
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


  // MARK: - Map Methods
 
  SDL_Point uiPosition(SDL_Point coordinates);
  SDL_Point mapPosition(SDL_Point uiPosition);
  bool checkBounds(SDL_Point min, SDL_Point max);

}

#endif /* Map_hpp */
