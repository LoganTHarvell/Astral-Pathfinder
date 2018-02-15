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

// MARK: Source Files
#include "GameObject.hpp"


class Planet: public GameObject {

public:
  // MARK: - Planet Constants
  static const int planetTexSize;

  
  // MARK: - Initialization Methods
  void initHomeworld();
  void initPlanet();
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  
  // MARK: - Planet Methods
  int getDeposits() { return deposits; };
  int getFertility() { return fertility; };
  
private:
  // MARK: - Planet Fields
  enum {
    undiscovered,
    discovered,
    colonized
  } status;

  // resources
  int deposits, fertility;
  
  // MARK: - Helper Methods
  SDL_Point uiPosition();
};

#endif /* Planet_hpp */
