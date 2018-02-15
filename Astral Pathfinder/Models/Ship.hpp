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

#define SHIP_WIDTH 24
#define SHIP_HEIGHT 45


class Ship: public GameObject {
  
public:
  // MARK: - Ship Constants
  const int population = 10000;
  const int velocity = 5;
  
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
