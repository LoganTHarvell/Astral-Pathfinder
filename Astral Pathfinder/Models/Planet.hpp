//
//  Planet.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/10/18.
//  Copyright © 2018 Ian Holdeman. All rights reserved.
//

#ifndef Planet_hpp
#define Planet_hpp

#include "SDL2/SDL.h"

class Planet {
public:
  Planet();
  ~Planet();
  
  SDL_Point position;
  
  // resources
  int deposits, fertility;
  
  enum {
    undiscovered,
    discovered,
    colonized
  } status;
};

#endif /* Planet_hpp */
