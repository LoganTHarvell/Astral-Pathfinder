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

class Ship {
  
public:
  const int population = 10000;
  const int velocity = 5;
  
  void init(SDL_Point position);
  
  void update();
  void render();
  
  SDL_Point getPosition() { return position; };
  int getFuel() { return fuel; };

private:
  SDL_Point position;
  int rotation;
  
  int fuel;
  
  SDL_Texture *texture;
  
  
  
};

#endif /* Ship_hpp */
