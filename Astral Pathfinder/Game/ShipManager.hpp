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
  // MARK: - ShipManager Initialization
  void init(SDL_Point homeworldPos);
  
  // MARK: - Game Loop Methods
  void update(Uint32 ticks);
  void render();
  
  // MARK: - Movement Method
  void shipMovement(SDL_Event e);
  
  Ship getPlayerShip() { return playerShip; };
  
private:
  // MARK: - ShipManager Fields
  Ship playerShip;
};

#endif /* ShipManager_hpp */
