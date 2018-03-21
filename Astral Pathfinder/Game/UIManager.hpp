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
#include "ShipInfo.hpp"

// MARK: - UIManager Parameters

namespace UiParameters {
  const SDL_Rect timeRect = { 16, 8, 75, 36 };
  const SDL_Rect shipInfoRect = {1215, 100, 320, 121};
  const SDL_Rect currentPlanetRect = {1215, 210, 320, 240};
  const SDL_Rect selectedPlanetRect = {1215, 500, 320, 300};
}

class UIManager {

public:
  // MARK: - UIManager Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager);
  void render(Game::State *gameState, PlanetManager *pm);
  
private:
  // MARK: - UIManager Fields
  // TODO: Implement main menu and endscreen
  // MainMenu mainMenu;
  TextBox time;
  PlanetInfo selectedPlanetInfo, DockedPlanetInfo;
  ShipInfo shipInfo;
  enum {
    none, currentPlanetWindow, selectedPlanetWindow
  } currentWindow = none;
  
  bool currentPlanetWindowCleaned = true, selectedPlanetWindowCleaned = true;
  // EndScreen endScreen;
  
  // MARK: - Helper Methods
  void updateTime(Uint32);
  void setSelectedPlanet(Planet p);
  void setDockedPlanet(Planet p);
  void handleMouseDown(Game::State *gs, PlanetManager *pm);
  void checkClickedArea(SDL_Point p);

};

#endif /* UIManager_hpp */
