//
//  UIManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef UIManager_hpp
#define UIManager_hpp

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "SDL2_ttf/SDL_ttf.h"

// MARK: Source Files
#include "Game.hpp"
#include "PlanetManager.hpp"
#include "PlanetInfo.hpp"
#include "ShipInfo.hpp"
#include "TextBox.hpp"
#include "EventsPanel.hpp"
#include "MainMenu.hpp"
#include "Scoreboard.hpp"
#include "EndScreen.hpp"


// MARK: - UIManager Class

class UIManager {

public:
  enum ScreenType {
    menu, scores, game, over, quit
  };
  
  // MARK: - UIManager Initialization
  void init(Game::State *gameState);
  void hotload();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager);
  void render(Game::State *gameState, PlanetManager *pm);
  
  // MARK: - Getter Methods
  ScreenType getActiveScreen() { return activeScreen; };
  bool checkStartScreens();
  
private:
  // MARK: - UIManager Fields
  TextBox time;
  TextBox totalScore, finalScore, playerName;
  EventsPanel eventsPanel;
  PlanetInfo selectedPlanetInfo, DockedPlanetInfo;
  ShipInfo shipInfo;
  SDL_Texture *hoverBorder = nullptr;
  SDL_Rect borderRect, screenRect;
  SDL_Texture *gameScreen = nullptr, *winScreen = nullptr;
  SDL_Texture *loseScreen = nullptr, *alienScreen = nullptr;
  int score, prevScore;
  SDL_Color prevColor, timeColor;
  MainMenu mainMenu;
  Scoreboard scoreboard;
  EndScreen endScreen;
  
  
  enum {
    none, currentPlanetWindow, selectedPlanetWindow
  } currentWindow = none;
  
  ScreenType activeScreen = menu;
  
  bool currentPlanetWindowCleaned = true, selectedPlanetWindowCleaned = true;
  bool mainMenuFlag, scoreboardFlag;
  
  // MARK: - Helper Methods
  void updateTime(Uint32);
  SDL_Color checkTime(int minutes);
  void updateTotalScore(PlanetManager *pm, Uint32 elapsedTime);
  SDL_Color setTotalScoreColor();
  void setSelectedPlanet(Planet p);
  void setDockedPlanet(Planet p);
  void handleMouseDown(Game::State *gs, PlanetManager *pm);
  void checkClickedArea(SDL_Point p);
  void checkSliderMovement(PlanetInfo *pi, Game::State *gs, PlanetManager *pm);
  void setActiveScreen(int screen);
  void setEndGameFlags(int nextScreen, Game::State *gs);
};

#endif /* UIManager_hpp */
