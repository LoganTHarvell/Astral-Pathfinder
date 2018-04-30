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
#include "PlayerShip.hpp"
#include "AlienShip.hpp"

namespace ShipManagerParameters {
  
  const Uint32 alienTargetingDelay = 60;
  
}

class ShipManager {
  
public:
  // MARK: - ShipManager Initialization
  void init(SDL_Point homeworldPos, SDL_Point alienPos);
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *pm);
  void render(Game::State *gameState);
  
  // MARK: - ShipManager Methods
  PlayerShip getPlayerShip() { return playerShip; };
  AlienShip getAlienShip() { return alienShip; };

  
private:
  // MARK: - ShipManager Fields
  PlayerShip playerShip;
  AlienShip alienShip;
  
  void setAlienTarget(Game::State *gs, PlanetManager *pm);
};

#endif /* ShipManager_hpp */
