//
//  UIManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef UIManager_hpp
#define UIManager_hpp

// MARK: Source Files
#include "Game.hpp"
#include "PlanetManager.hpp"
#include "PlanetInfo.hpp"

class UIManager {

public:
  // MARK: - UIManager Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *planetManager);
  void render(Game::State *gameState);
  
private:
  // MARK: - UIManager Fields
  // TODO: Implement main menu and endscreen
  // MainMenu mainMenu;
  PlanetInfo planetInfo;
  // EndScreen endScreen;
  
  // MARK: - Helper Methods
  void setSelectedPlanet(Planet p);

};

#endif /* UIManager_hpp */
