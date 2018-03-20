//
//  ShipManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef ShipManager_hpp
#define ShipManager_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "Game.hpp"
#include "PlanetManager.hpp"
#include "Ship.hpp"

class ShipManager {
  
public:
  // MARK: - ShipManager Initialization
  void init(SDL_Point homeworldPos);
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *pm);
  void render(Game::State *gameState);
  
  // MARK: - ShipManager Methods
  Ship getPlayerShip() { return playerShip; };
  
private:
  // MARK: - ShipManager Fields
  Ship playerShip;
};

#endif /* ShipManager_hpp */
