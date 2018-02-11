//
//  Galaxy.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Galaxy_hpp
#define Galaxy_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "parameters.h"
#include "GameObject.hpp"


class Galaxy {
  
public:
  Galaxy();
  ~Galaxy();
  
  struct Planet {
    SDL_Point position;
    
    // resources
    int fertility;
    int deposits;
    
    enum {
      undiscovered,
      discovered,
      colonized
    } status;
  };
  
  Planet planets[NUMBER_OF_PLANETS];
  
private:
  static Planet initHomeworld();
  static Planet initPlanet();
  
};

#endif /* Galaxy_hpp */
