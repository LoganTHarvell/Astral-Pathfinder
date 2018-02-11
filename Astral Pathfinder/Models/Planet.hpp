//
//  Planet.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Planet_hpp
#define Planet_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

#include "parameters.h"

class Planet {
public:
    Planet();
    ~Planet();
  
    void initHomeworld();
    void initPlanet();
    int getPositionX();
    int getPositionY();
    int getDeposits();
    int getFertility();
  
private:
    SDL_Point position;
  
    enum {
      undiscovered,
      discovered,
      colonized
    } status;
  
    // resources
    int deposits, fertility;
};

#endif /* Planet_hpp */
