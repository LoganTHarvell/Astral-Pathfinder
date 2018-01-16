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

#define GRID_SIZE MAP_WIDTH/NUMBER_OF_PLANETS
#define PLANET_TEXTURE_SIZE 8
#define PLANET_TEXTURE_OFFSET (GRID_SIZE - PLANET_TEXTURE_SIZE)

class Galaxy {
  
  struct Planet {
    
    enum Status {
      undiscovered,
      discovered,
      colonized
    };
    
    int xpos, ypos;
    int fertility;
    int deposits;
    Status status;
    GameObject* gameObject;
    
  };
  
public:
  Galaxy();
  ~Galaxy();

  Planet planets[NUMBER_OF_PLANETS];
 
  void update();
  void render();
  
private:
  static const SDL_Rect planetSrcRect;
  bool hasPlanet[NUMBER_OF_PLANETS][NUMBER_OF_PLANETS] = { false };
  
  static Planet initHomeworld();
  static Planet initPlanet();
  
};

#endif /* Galaxy_hpp */
