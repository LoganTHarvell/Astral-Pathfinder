//
//  Galaxy.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Galaxy_hpp
#define Galaxy_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "parameters.h"
#include "GameObject.hpp"
#include "Planet.hpp"


class PlanetManager {
  
public:
  PlanetManager();
  ~PlanetManager();
  
  Planet planets[NUMBER_OF_PLANETS];
  
private:
  static Planet initHomeworld();
  static Planet initPlanet();
  
};

#endif /* Galaxy_hpp */
