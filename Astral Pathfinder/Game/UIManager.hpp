//
//  UIManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Manager class responsible for managing all UI elements, specifically
//  initializing, updating, and rendering. It handles UI elements as
//  groupings by screen. Some sub-screens that handle their own individual
//  initializing, updating, and rendering.

#ifndef UIManager_hpp
#define UIManager_hpp

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "SDL2_ttf/SDL_ttf.h"

// MARK: Source Files
#include "Game.hpp"
#include "PlanetManager.hpp"
#include "ShipManager.hpp"
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
  // MARK: - UIManager Initialization
  void init(Game::State *gameState);
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager);
  void render(Game::State *gameState, PlanetManager *pm);
  
  // MARK: - Getter Methods
  Screen::ID getActiveScreen() { return activeScreen; };
  bool checkStartScreens();
  
private:  
  // MARK: - UIManager Screens
  
  // TODO: Move all gameplay UI elements to a gameplayScreen
  TextBox time;
  TextBox totalScore, finalScore, playerName;
  EventsPanel eventsPanel;
  PlanetInfo selectedPlanetInfo, DockedPlanetInfo;
  ShipInfo shipInfo;
  SDL_Rect borderRect, screenRect;
  SDL_Texture *gameScreen = nullptr;
  SDL_Color prevColor, timeColor;
  
  MainMenu mainMenu;
  Scoreboard scoreboard;
  EndScreen endScreen;
  
  enum {
    none, currentPlanetWindow, selectedPlanetWindow
  } currentWindow = none;
  
  Screen::ID activeScreen = Screen::ID::menu;
  
  bool currentPlanetWindowCleaned = true, selectedPlanetWindowCleaned = true;
  bool mainMenuFlag, scoreboardFlag;
 
  int score, prevScore;
  
  // MARK: - Helper Methods
  
  void updateTime(Uint32);
  SDL_Color checkTime(Uint32 elapsedTime);
  
  void updateTotalScore(PlanetManager *pm, Uint32 elapsedTime);
  
  // Setters
  SDL_Color setTotalScoreColor();
  void setSelectedPlanet(Planet p);
  void setDockedPlanet(Planet p);
  void setActiveScreen(Screen::ID screen);
  void setEndGameFlags(Screen::ID nextScreen, Game::State *gs);
  
  // Event Handling
  void handleMouseDown(Game::State *gs, PlanetManager *pm);
  void checkClickedArea(SDL_Point p);
  void checkSliderMovement(PlanetInfo *pi, Game::State *gs, PlanetManager *pm);

};

#endif /* UIManager_hpp */
