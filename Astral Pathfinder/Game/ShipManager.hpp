//
//  ShipManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef ShipManager_hpp
#define ShipManager_hpp

#include "SDL2/SDL.h"

#include "Ship.hpp"



class ShipManager {
  
public:
  void init(SDL_Point homeworldPos);
  
  void update();
  void render();
  
private:
  Ship playerShip;
};

#endif /* ShipManager_hpp */
