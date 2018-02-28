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
    int w = 48, h = 24;
  } shipSize;
  
  const int population = 10000;
  // TODO: figure out real velocity/ticks formula
  const int speed = 1;
  const int turnSpeed = 5;
}


// MARK: - Ship Class

class Ship: public GameObject {
  
public:
  // MARK: - Initialization Methods
  void init(SDL_Point position);
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  
  // MARK: - Ship Methods
  int getFuel() { return fuel; };
  int getRotation() { return rotation; };
  void move(Uint32 ticks);
  

private:
  // MARK: - Ship Fields
  int rotation;
  int fuel;
  SDL_Point velocity;
  
  // MARK: - Helper Methods
  SDL_Point mapPosition(SDL_Point p);
  bool boundaryCollision();
  
  void updateVelocity();
  void updateRotation();
};

#endif /* Ship_hpp */
