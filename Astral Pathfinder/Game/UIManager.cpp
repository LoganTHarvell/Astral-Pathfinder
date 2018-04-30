//
//  UIManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "UIManager.hpp"

// MARK: Libraries and Frameworks
#include <string>
#include "SDL2_ttf/SDL_ttf.h"

// MARK: Source Files
#include "TextureManager.hpp"

// MARK: - UIManager Initialization

void UIManager::init() {
  using namespace UiParameters;

  time.init(timeRect);
  totalScore.init(totalScoreRect);
  eventsPanel.init();
  selectedPlanetInfo.init(selectedPlanetRect);
  DockedPlanetInfo.init(currentPlanetRect);
  shipInfo.init(shipInfoRect);
  finalScore.init({endScoreCoords.x, endScoreCoords.y, 0, 0});
  hoverBorder = TextureManager::loadTexture("../Resources/border.png");
  
  mainMenu = TextureManager::loadTexture("../Resources/mainMenu.png");
  gameScreen = TextureManager::loadTexture("../Resources/gameScreen.png");
  winScreen = TextureManager::loadTexture("../Resources/winScreen.png");
  loseScreen = TextureManager::loadTexture("../Resources/loseScreen.png");
  screenRect = { 0, 0, GameParameters::windowRect.w, GameParameters::windowRect.h };
  
  mainMenuFlag = true;
  prevScore = 0;
}

// MARK: - Game Loop Methods

void UIManager::update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager) {
  if (mainMenuFlag) {
    checkForHovering(gameState);
    if(gameState->mouseDown)
      checkClickedAreaOtherScreen(gameState);
    
    return;
  }
  else if (gameState->endgame == Game::State::quit) {
    mainMenuFlag = false;
    gameState->isRunning = false;
    return;
  }
  else if (gameState->gameOver){
    mainMenuFlag = false;
    checkForHovering(gameState);
    if(gameState->mouseDown) checkClickedAreaOtherScreen(gameState);

    return;
  }
  
  updateTime(gameState->elapsedTime);
  updateTotalScore(planetManager);
  eventsPanel.update(gameState, planetManager);
  
  PlayerShip player = shipManager->getPlayerShip();
  if(player.getVelocity().x != 0 || player.getVelocity().y != 0
     || planetManager->playerIsDocked()) {
    shipInfo.clean();
    shipInfo.setText(player);
  }
  
  if (gameState->planetSelected) {
    setSelectedPlanet(planetManager->getSelectedPlanet());
    selectedPlanetWindowCleaned = false;
  }
  else if(!selectedPlanetWindowCleaned) {
    selectedPlanetInfo.clean();
    selectedPlanetWindowCleaned = true;
  }
  
  if(planetManager->playerIsDocked()) {
    setDockedPlanet(planetManager->getPlayerDockedPlanet());
    currentPlanetWindowCleaned = false;
  }
  else if(!currentPlanetWindowCleaned) {
    DockedPlanetInfo.clean();
    currentPlanetWindowCleaned = true;
  }
  
  handleMouseDown(gameState, planetManager);
}

void UIManager::render(Game::State *gameState, PlanetManager *pm) {
  using namespace UiParameters;
  if (mainMenuFlag) {
    SDL_RenderCopy(Game::renderer, mainMenu, NULL, &screenRect);
    if(hoveringLabel == startGame)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    else if(hoveringLabel == scoreboard)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    else if(hoveringLabel == exitGame)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    return;
  }
  else if (gameState->gameOver && gameState->endgame != Game::State::quit) {
    if(gameState->endgame == Game::State::allDiscovered)
      SDL_RenderCopy(Game::renderer, winScreen, NULL, &screenRect);
    else if(gameState->endgame == Game::State::noFuel)
      SDL_RenderCopy(Game::renderer, loseScreen, NULL, &screenRect);
    
    if(finalScore.checkNull())
      finalScore.setFinalScore(std::to_string(score).c_str());
    
    finalScore.render(gameState);
    
    if(hoveringLabel == playAgain)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    else if(hoveringLabel == endGameExit)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    return;
  }
  else if(!gameState->gameOver) {
    SDL_RenderCopy(Game::renderer, gameScreen, NULL, &screenRect);
  
    time.render(gameState);
    totalScore.render(gameState);
    eventsPanel.render(gameState);
    shipInfo.render(gameState);
    
    if(gameState->planetSelected) {
      Planet selectedP = pm->getSelectedPlanet();
      selectedPlanetInfo.render(gameState, selectedP.getPopulation(),
                                selectedP.playerIsDocked());
    }
    if(gameState->playerCollision) {
      Planet dockedP = pm->getPlayerDockedPlanet();
      DockedPlanetInfo.render(gameState, dockedP.getPopulation(),
                              dockedP.playerIsDocked());
    }
  }
}

// MARK: - UIManager Methods

void UIManager::updateTime(Uint32 elapsedTime) {
  int minutes = elapsedTime / 60;
  std::string secs = std::to_string(elapsedTime % 60);
  std::string mins = std::to_string(minutes);
  time.setMessage(mins + ":" + secs, checkTime(minutes));
}

SDL_Color UIManager::checkTime(int minutes) {
  if(minutes < 15) return UiParameters::green;
  else if(minutes < 20) return UiParameters::yellow;
  else return UiParameters::red;
}

void UIManager::updateTotalScore(PlanetManager *pm) {
  score = pm->getTotalPopulation();
  std::string population = std::to_string(score);
  totalScore.setMessage(population, setTotalScoreColor());

  prevScore = score;
}

SDL_Color UIManager::setTotalScoreColor() {
  if(prevScore == score)
    return prevColor;
  else if(prevScore < score) {
    prevColor = UiParameters::green;
    return UiParameters::green;
  }
  else {
    prevColor = UiParameters::red;
    return UiParameters::red;
  }
}

void UIManager::setSelectedPlanet(Planet p) {
  selectedPlanetInfo.setUiTextures(p);
}

void UIManager::setDockedPlanet(Planet p) {
  DockedPlanetInfo.setUiTextures(p);
}

void UIManager::handleMouseDown(Game::State *gs, PlanetManager *pm) {
  enum {
    neither, fertilitySlider, reserveSlider
  };
  
  // If mouse button not pressed down, don't check for slider movement
  if(!gs->mouseDown) return;
  
  if(gs->mouseDown)
    checkClickedArea(gs->clickLocation);
  
  // Current Planet Window
  if(currentWindow == currentPlanetWindow) {
    // If down, but not dragging, check if slider was clicked
    if(gs->mouseDown && gs->activeSlider == gs->State::inactive) {
      if(DockedPlanetInfo.checkClick(gs->clickLocation) == fertilitySlider)
        gs->activeSlider = gs->State::currentOne;
      
      if(DockedPlanetInfo.checkClick(gs->clickLocation) == reserveSlider)
        gs->activeSlider = gs->State::currentTwo;
    }
  
    // If so, check mouse movement and adjust slider appropriately
    if(gs->activeSlider == gs->State::currentOne) {
      bool movement = DockedPlanetInfo.moveSlider(gs);
      int percent = DockedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetMiningPercent(100-percent, currentWindow);
        pm->setPlanetFarmingPercent(percent, currentWindow);
      }
    }
  
    if(gs->activeSlider == gs->State::currentTwo) {
      bool movement = DockedPlanetInfo.moveSlider(gs);
      int percent = DockedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetInfraPercent(100-percent, currentWindow);
        pm->setPlanetReservePercent(percent, currentWindow);
      }
    }
  }
  
  // Selected Planet Window
  if(currentWindow == selectedPlanetWindow) {
    // If down, but not dragging, check if slider was clicked
    if(gs->mouseDown && gs->activeSlider == gs->State::inactive) {
      if(selectedPlanetInfo.checkClick(gs->clickLocation) == fertilitySlider)
        gs->activeSlider = gs->State::selectOne;
      
      if(selectedPlanetInfo.checkClick(gs->clickLocation) == reserveSlider)
        gs->activeSlider = gs->State::selectTwo;
    }
    
    // If so, check mouse movement and adjust slider appropriately
    if(gs->activeSlider == gs->State::selectOne) {
      bool movement = selectedPlanetInfo.moveSlider(gs);
      int percent = selectedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetMiningPercent(100-percent, currentWindow);
        pm->setPlanetFarmingPercent(percent, currentWindow);
      }
    }
    
    if(gs->activeSlider == gs->State::selectTwo) {
      bool movement = selectedPlanetInfo.moveSlider(gs);
      int percent = selectedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetInfraPercent(100-percent, currentWindow);
        pm->setPlanetReservePercent(percent, currentWindow);
      }
    }
  }
}

void UIManager::checkClickedArea(SDL_Point p) {
  using namespace UiParameters;
  if((p.x > currentPlanetRect.x) && (p.x < currentPlanetRect.x + currentPlanetRect.w)
     && (p.y > currentPlanetRect.y) && (p.y < currentPlanetRect.y + currentPlanetRect.h))
    currentWindow = currentPlanetWindow;
  
  else if((p.x > selectedPlanetRect.x) && (p.x < selectedPlanetRect.x + selectedPlanetRect.w)
          && (p.y > selectedPlanetRect.y) && (p.y < selectedPlanetRect.y + selectedPlanetRect.h))
    currentWindow = selectedPlanetWindow;
  
  else currentWindow = none;
}

void UIManager::checkForHovering(Game::State *gs) {
  using namespace UiParameters;
  SDL_Point p = gs->dragLocation;
  int buffer = 11;
  
  // Main Menu
  if(mainMenuFlag) {
    if((p.x > startGameLabel.x) && (p.x < startGameLabel.x + startGameLabel.w)
       && (p.y > startGameLabel.y) && (p.y < startGameLabel.y + startGameLabel.h)) {
      hoveringLabel = startGame;
      
      if(borderRect.y != startGameLabel.y-buffer)
        borderRect = startGameBorder;
    }
  
    else if((p.x > scoreboardLabel.x) && (p.x < scoreboardLabel.x + scoreboardLabel.w)
            && (p.y > scoreboardLabel.y) && (p.y < scoreboardLabel.y + scoreboardLabel.h)) {
      hoveringLabel = scoreboard;
      
      if(borderRect.y != scoreboardLabel.y-buffer)
        borderRect = scoreboardBorder;
    }
  
    else if((p.x > exitGameLabel.x) && (p.x < exitGameLabel.x + exitGameLabel.w)
            && (p.y > exitGameLabel.y) && (p.y < exitGameLabel.y + exitGameLabel.h)) {
      hoveringLabel = exitGame;
      
      if(borderRect.y != exitGameLabel.y-buffer)
        borderRect = exitGameBorder;
    }
  
    else hoveringLabel = nothing;
  }
  
  // End Screen
  else if(gs->gameOver && gs->endgame != Game::State::quit) {
    if((p.x > playAgainLabel.x) && (p.x < playAgainLabel.x + playAgainLabel.w)
       && (p.y > playAgainLabel.y) && (p.y < playAgainLabel.y + playAgainLabel.h)) {
      hoveringLabel = playAgain;
      
      if(borderRect.y != playAgainLabel.y-buffer)
        borderRect = playAgainBorder;
    }
    
    else if((p.x > endGameExitLabel.x) && (p.x < endGameExitLabel.x + endGameExitLabel.w)
            && (p.y > endGameExitLabel.y) && (p.y < endGameExitLabel.y + endGameExitLabel.h)) {
      hoveringLabel = endGameExit;
      
      if(borderRect.y != endGameExitLabel.y-buffer)
        borderRect = endGameBorder;
    }
    
    else hoveringLabel = nothing;
  }
}

void UIManager::checkClickedAreaOtherScreen(Game::State *gs) {
  SDL_Point p = gs->clickLocation;
  using namespace UiParameters;
  
  // Main Menu
  if(mainMenuFlag) {
    if((p.x > startGameLabel.x) && (p.x < startGameLabel.x + startGameLabel.w)
       && (p.y > startGameLabel.y) && (p.y < startGameLabel.y + startGameLabel.h)) {
      hoveringLabel = nothing;
      mainMenuFlag = false;
    }
  
  // Future score board
   /* else if((p.x > scoreboardLabel.x) && (p.x < scoreboardLabel.x + scoreboardLabel.w)
            && (p.y > scoreboardLabel.y) && (p.y < scoreboardLabel.y + scoreboardLabel.h))
    */
  
    else if((p.x > exitGameLabel.x) && (p.x < exitGameLabel.x + exitGameLabel.w)
       && (p.y > exitGameLabel.y) && (p.y < exitGameLabel.y + exitGameLabel.h)) {
      hoveringLabel = nothing;
      mainMenuFlag = false;
      gs->endgame = Game::State::quit;
    }
  }
  
  // End Screen
  else if(gs->gameOver && gs->endgame != Game::State::quit) {
    if((p.x > playAgainLabel.x) && (p.x < playAgainLabel.x + playAgainLabel.w)
       && (p.y > playAgainLabel.y) && (p.y < playAgainLabel.y + playAgainLabel.h)) {
      gs->frame = 0;
      gs->gameOver = false;
      gs->endgameFrame = 0;
      hoveringLabel = nothing;
      mainMenuFlag = true;
      gs->endgame = Game::State::none;
      gs->restartGame = true;
      gs->mouseDown = false;
    }
    
    else if((p.x > endGameExitLabel.x) && (p.x < endGameExitLabel.x + endGameExitLabel.w)
            && (p.y > endGameExitLabel.y) && (p.y < endGameExitLabel.y + endGameExitLabel.h)) {
      hoveringLabel = nothing;
      mainMenuFlag = false;
      gs->endgame = Game::State::quit;
    }
  }
}
