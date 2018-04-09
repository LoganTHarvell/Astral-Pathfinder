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
  const SDL_Rect timeRect = {115, 82, 90, 36};
  const SDL_Rect totalScoreRect = {245, 82, 90, 36};
  const SDL_Rect shipInfoRect = {1215, 100, 320, 121};
  const SDL_Rect currentPlanetRect = {1215, 210, 320, 240};
  const SDL_Rect selectedPlanetRect = {1215, 500, 320, 300};
  const SDL_Rect startGameLabel = {600, 401, 424, 57};
  const SDL_Rect scoreboardLabel = {600, 538, 424, 58};
  const SDL_Rect exitGameLabel = {600, 676, 424, 54};
  const SDL_Rect playAgainLabel = {288, 673, 424, 57};
  const SDL_Rect endGameExitLabel = {885, 676, 424, 54};
  const SDL_Rect startGameBorder = {582, 390, 460, 95};
  const SDL_Rect scoreboardBorder = {582, 527, 460, 96};
  const SDL_Rect exitGameBorder = {582, 665, 460, 92};
  const SDL_Rect playAgainBorder = {270, 662, 460, 95};
  const SDL_Rect endGameBorder = {867, 665, 460, 92};
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
  
private:
  // MARK: - UIManager Fields
  TextBox time;
  TextBox totalScore;
  PlanetInfo selectedPlanetInfo, DockedPlanetInfo;
  ShipInfo shipInfo;
  SDL_Texture *hoverBorder;
  SDL_Rect borderRect, screenRect;
  SDL_Texture *mainMenu, *gameScreen, *winScreen, *loseScreen;
  enum {
    none, currentPlanetWindow, selectedPlanetWindow
  } currentWindow = none;
  
  enum {
    nothing, startGame, scoreboard, exitGame, playAgain, endGameExit
  } hoveringLabel = nothing;
  
  bool currentPlanetWindowCleaned = true, selectedPlanetWindowCleaned = true;
  bool mainMenuFlag;
  
  // MARK: - Helper Methods
  void updateTime(Uint32);
  void updateTotalScore(PlanetManager *pm);
  void setSelectedPlanet(Planet p);
  void setDockedPlanet(Planet p);
  void handleMouseDown(Game::State *gs, PlanetManager *pm);
  void checkClickedArea(SDL_Point p);
  void checkForHovering(Game::State *gs);
  void checkClickedAreaOtherScreen(Game::State *gs);
};

#endif /* UIManager_hpp */
