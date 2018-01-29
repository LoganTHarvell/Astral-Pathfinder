//
//  Galaxy.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
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
  struct Planet {
    
    enum Status {
      undiscovered,
      discovered,
      colonized
    };
    
    SDL_Point position;
    int fertility;
    int deposits;
    Status status;
  };
  
  Galaxy();
  ~Galaxy();

  Planet planets[NUMBER_OF_PLANETS];
  
private:
  bool hasPlanet[NUMBER_OF_PLANETS][NUMBER_OF_PLANETS] = { false };
  
  static Planet initHomeworld();
  static Planet initPlanet();
  
};

#endif /* Galaxy_hpp */
