//
//  Ship.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "GameObject.hpp"


// MARK: - Ship Parameters

namespace ShipParameters {
  
  const struct {
    int w = 24, h = 45;
  } shipSize;
  
  const int population = 10000;
  const int velocity = 5;
  
}


// MARK: - Ship Class
class Ship: public GameObject {
  
public:
  
  // MARK: - Initialization Methods
  void init(SDL_Point position);
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  
  // MARK: - Helper Methods
  int getFuel() { return fuel; };

private:
  // MARK: - Ship Fields
  int rotation;
  int fuel;
  
  // MARK: - Helper Methods
  SDL_Point uiPosition();
};

#endif /* Ship_hpp */
