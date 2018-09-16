//
//  Map.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Namespace containing information about the map space where the planet and
//  ship game elements are displayed. Functions are declared for calculating
//  various contextual information between the map and the game elements.

#ifndef Map_hpp
#define Map_hpp

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: - Map Namespace

namespace Map {
  using namespace Parameters::UI::Map;
  using Parameters::PlanetManager::numberOfPlanets;
  using Parameters::Planet::planetTexSize;
  
  // MARK: - Map Parameters
  
  const SDL_Point gridOrigin = { rect.x + (gridOffset/2),
                                 rect.y + (gridOffset/2) };
  const int gridWidth = (rect.w - gridOffset)/numberOfPlanets;
  const int gridHeight = (rect.h - gridOffset)/numberOfPlanets;

  // MARK: - Map Functions
 
  SDL_Point uiPosition(SDL_Point coordinates);
  SDL_Point mapPosition(SDL_Point uiPosition);
  bool checkBounds(SDL_Point min, SDL_Point max);
}


#endif /* Map_hpp */
