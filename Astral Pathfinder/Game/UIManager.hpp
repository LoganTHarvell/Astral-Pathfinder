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

// MARK: - UIManager Parameters

namespace UiParameters {
  const SDL_Rect timeRect = {115, 82, 90, 36};
  const SDL_Rect totalScoreRect = {245, 82, 90, 36};
  const SDL_Rect shipInfoRect = {1215, 100, 320, 121};
  const SDL_Rect currentPlanetRect = {1215, 210, 320, 240};
  const SDL_Rect selectedPlanetRect = {1215, 500, 320, 300};
  const SDL_Rect startGameLabel = {600, 401, 424, 57};
  const SDL_Rect scoreboardLabel = {600, 538, 424, 58};
  const SDL_Rect exitGameLabel = {600, 676, 424, 54};
  const SDL_Rect playAgainLabel = {288, 673, 424, 57};
  const SDL_Rect mainMenuLabel = {885, 677, 424, 54};
  const SDL_Rect mainMenuScoreboardLabel = {628, 754, 376, 67};
  const SDL_Rect startGameBorder = {582, 390, 460, 95};
  const SDL_Rect scoreboardBorder = {582, 527, 460, 96};
  const SDL_Rect exitGameBorder = {582, 665, 460, 92};
  const SDL_Rect playAgainBorder = {270, 662, 460, 95};
  const SDL_Rect mainMenuBorder = {867, 666, 460, 92};
  const SDL_Rect mainMenuScoreboardBorder = {609, 742, 412, 90};
  const SDL_Rect startingNameBox = {760, 203, 300, 42};
  const SDL_Rect startingScoreBox = {880, 203, 300, 42};
  const SDL_Point endScoreCoords = {945, 335};
  const SDL_Point endScoreName = {940, 480};
  const SDL_Color red = {128,0,0};
  const SDL_Color green = {0,128,0};
  const SDL_Color yellow = {255, 255, 0};
  const std::string filePath = "Resources/Scores/scoreboard.txt";
  const int scoreboardMax = 10;
}

class UIManager {

public:
  // MARK: - UIManager Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager);
  void render(Game::State *gameState, PlanetManager *pm);
  
  // MARK: - Helper Methods
  bool checkMainMenu() { return mainMenuFlag; }
  bool checkScoreboardScreen() { return scoreboardFlag; }
  void setMainMenuFlag(bool flag) { mainMenuFlag = flag; }
  
private:
  // MARK: - UIManager Fields
  TextBox time;
  TextBox totalScore, finalScore, playerName;
  EventsPanel eventsPanel;
  PlanetInfo selectedPlanetInfo, DockedPlanetInfo;
  ShipInfo shipInfo;
  SDL_Texture *hoverBorder;
  SDL_Rect borderRect, screenRect;
  SDL_Texture *mainMenu, *scoreboardTex, *gameScreen, *winScreen, *loseScreen;
  int score, prevScore;
  SDL_Color prevColor, timeColor;
  
  enum {
    none, currentPlanetWindow, selectedPlanetWindow
  } currentWindow = none;
  
  enum {
    nothing, startGame, scoreboard, exitGame, playAgain, mainMenuExit, mainMenuScoreboard
  } hoveringLabel = nothing;
  
  bool currentPlanetWindowCleaned = true, selectedPlanetWindowCleaned = true;
  bool mainMenuFlag, scoreboardFlag;
  TextBox scoreList[20];
  int scores[10] = {-1};
  std::string names[10] = {""};
  
  // MARK: - Helper Methods
  void updateTime(Uint32);
  SDL_Color checkTime(int minutes);
  void updateTotalScore(PlanetManager *pm);
  SDL_Color setTotalScoreColor();
  void setSelectedPlanet(Planet p);
  void setDockedPlanet(Planet p);
  void handleMouseDown(Game::State *gs, PlanetManager *pm);
  void checkClickedArea(SDL_Point p);
  void checkForHovering(Game::State *gs);
  void checkClickedAreaOtherScreen(Game::State *gs);
  void writeScore(Game::State *gs);
  void readScores();
  void compareScores(std::string name, int score);
};

#endif /* UIManager_hpp */
