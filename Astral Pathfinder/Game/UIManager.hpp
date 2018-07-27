//
//  UIManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef UIManager_hpp
#define UIManager_hpp

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

// MARK: - UIManager Parameters

namespace UiParameters {
  const SDL_Rect timeRect = {115, 82, 90, 36};
  const SDL_Rect totalScoreRect = {245, 82, 90, 36};
  const SDL_Rect shipInfoRect = {1215, 100, 320, 121};
  const SDL_Rect currentPlanetRect = {1215, 210, 320, 240};
  const SDL_Rect selectedPlanetRect = {1215, 500, 320, 300};
  const SDL_Point endScoreCoords = {945, 335};
  const SDL_Point endScoreName = {940, 480};
  const SDL_Color red = {128,0,0};
  const SDL_Color green = {0,128,0};
  const SDL_Color yellow = {255, 255, 0};
}

class UIManager {

public:
  // MARK: - UIManager Initialization
  void init(Game::State *gameState);
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager);
  void render(Game::State *gameState, PlanetManager *pm);
  
  // MARK: - Helper Methods
  bool checkGameScreen();
  bool checkStartScreens();
  
private:
  // MARK: - UIManager Fields
  TextBox time;
  TextBox totalScore, finalScore, playerName;
  EventsPanel eventsPanel;
  PlanetInfo selectedPlanetInfo, DockedPlanetInfo;
  ShipInfo shipInfo;
  SDL_Texture *hoverBorder;
  SDL_Rect borderRect, screenRect;
  SDL_Texture *gameScreen, *winScreen, *loseScreen, *alienScreen;
  int score, prevScore;
  SDL_Color prevColor, timeColor;
  MainMenu mainMenu;
  Scoreboard scoreboard;
  EndScreen endScreen;
  
  
  enum {
    none, currentPlanetWindow, selectedPlanetWindow
  } currentWindow = none;
  
  enum {
    menu, scores, game, over
  } activeScreen = menu;
  
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
};

#endif /* UIManager_hpp */
