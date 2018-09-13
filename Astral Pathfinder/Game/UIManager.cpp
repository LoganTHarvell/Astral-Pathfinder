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
#include "SDL2_ttf/SDL_ttf.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "TextureManager.hpp"


// MARK: - UIManager Initialization

void UIManager::init(Game::State *gameState) {
  using namespace Parameters::UIManager;

  time.init(timeRect);
  totalScore.init(totalScoreRect);
  eventsPanel.init();
  selectedPlanetInfo.init(selectedPlanetRect);
  DockedPlanetInfo.init(currentPlanetRect);
  shipInfo.init(shipInfoRect);
  finalScore.init({endScoreCoords.x, endScoreCoords.y, 0, 0});
  playerName.init({endNameCoords.x, endNameCoords.y, 0, 0});
  
  TextureManager::loadTexture(gameScreenFile, &gameScreen, Game::renderer);
  
  prevScore = 0;
  
  mainMenu.init();
  scoreboard.init();
  endScreen.init();
  
  if (gameState->skipMainMenu)
    activeScreen = game;
}

// TODO: Enable hotloading, delete and reinitialize ?
//void UIManager::hotload() {
//  using namespace Parameters::UIManager;
//
//  time.init(timeRect);
//  totalScore.init(totalScoreRect);
//  eventsPanel.init();
//  selectedPlanetInfo.init(selectedPlanetRect);
//  DockedPlanetInfo.init(currentPlanetRect);
//  shipInfo.init(shipInfoRect);
//  finalScore.init({endScoreCoords.x, endScoreCoords.y, 0, 0});
//  playerName.init({endNameCoords.x, endNameCoords.y, 0, 0});
//
//  SDL_DestroyTexture(gameScreen);
//  TextureManager::loadTexture(gameScreenFile, &gameScreen, Game::renderer);
//
//  mainMenu.init();
//  scoreboard.init();
//  endScreen.init();
//}

// MARK: - Game Loop Methods

void UIManager::update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager) {
  
  // If user quits, end the game
  if (gameState->endgame == Game::State::quit) {
    gameState->isRunning = false;
  }
  
  // If on the main menu
  else if (activeScreen == menu) {
    mainMenu.checkForHovering(gameState, activeScreen);
    if (gameState->mouseDown) {
      int newScreen = mainMenu.checkClick(gameState, activeScreen);
      if (newScreen != -1)
        setActiveScreen(newScreen);
    }
  }
  
  // If on scoreboard
  else if (activeScreen == scores) {
    scoreboard.checkForHovering(gameState, activeScreen);
    if (gameState->mouseDown) {
      int newScreen = scoreboard.checkClick(gameState, activeScreen);
      if (newScreen != -1)
        setActiveScreen(newScreen);
    }
  }
  
  // End game screen
  else if (gameState->gameOver) {
    if (!SDL_IsTextInputActive())
      SDL_StartTextInput();
    endScreen.update(gameState);
    endScreen.checkForHovering(gameState, over);
    if (gameState->mouseDown) {
      int newScreen = endScreen.checkClick(gameState, over);
      if (newScreen != -1) {
        setActiveScreen(newScreen);
        SDL_StopTextInput();
        scoreboard.writeScore(gameState, score);
        setEndGameFlags(newScreen, gameState);
      }
    }
  }
  
  // Playing the game
  else {
    updateTime(gameState->elapsedTime);
    updateTotalScore(planetManager, gameState->elapsedTime);
    eventsPanel.update(gameState, planetManager);
    
    PlayerShip player = shipManager->getPlayerShip();
    if (player.getVelocity().x != 0 || player.getVelocity().y != 0
       || planetManager->playerIsDocked()) {
      shipInfo.clean();
      shipInfo.setText(player);
    }
    
    if (gameState->planetSelected) {
      setSelectedPlanet(planetManager->getSelectedPlanet());
      selectedPlanetWindowCleaned = false;
    }
    else if (!selectedPlanetWindowCleaned) {
      selectedPlanetInfo.clean();
      selectedPlanetWindowCleaned = true;
    }
    
    if (planetManager->playerIsDocked()) {
      setDockedPlanet(planetManager->getPlayerDockedPlanet());
      currentPlanetWindowCleaned = false;
    }
    else if (!currentPlanetWindowCleaned) {
      DockedPlanetInfo.clean();
      currentPlanetWindowCleaned = true;
    }
    
    handleMouseDown(gameState, planetManager);
  }
  
  if (activeScreen == quit)
    gameState->endgame = Game::State::quit;
}

void UIManager::render(Game::State *gameState, PlanetManager *pm) {
  using namespace Parameters::UIManager;
  
  // Main Menu
  if (activeScreen == menu) {
    mainMenu.render(gameState);
  }
  
  // Scoreboard
  else if (activeScreen == scores) {
    scoreboard.render(gameState);
  }
  
  // Game Over
  else if (gameState->gameOver && gameState->endgame != Game::State::quit) {
    endScreen.render(gameState);
    
    if (finalScore.checkNull())
      finalScore.setFinalScore(std::to_string(score).c_str());
    finalScore.render(gameState);
    
    if (gameState->renderPlayerName) {
      playerName.setFinalScore(gameState->playerName.c_str());
      gameState->renderPlayerName = false;
    }
    
    playerName.render(gameState);
  }
  
  // Game
  else if (!gameState->gameOver && gameState->endgame != Game::State::quit) {
    SDL_RenderCopy(Game::renderer, gameScreen, NULL,
                   &Parameters::UIManager::screenRect);
  
    time.render(gameState);
    totalScore.render(gameState);
    eventsPanel.render(gameState);
    shipInfo.render(gameState);
    
    if (gameState->planetSelected) {
      Planet selectedP = pm->getSelectedPlanet();
      selectedPlanetInfo.render(gameState, selectedP.getPopulation(),
                                selectedP.playerIsDocked());
    }
    if (gameState->playerCollision) {
      Planet dockedP = pm->getPlayerDockedPlanet();
      DockedPlanetInfo.render(gameState, dockedP.getPopulation(),
                              dockedP.playerIsDocked());
    }
  }
}


// MARK: - UIManager Methods

// Helper method to check for both screens in one call
bool UIManager::checkStartScreens() {
  if (activeScreen == menu || activeScreen == scores)
    return true;
  
  return false;
}

// Updates time spent playing
void UIManager::updateTime(Uint32 elapsedTime) {
  int minutes = elapsedTime / 60;
  std::string secs = std::to_string(elapsedTime % 60);
  std::string mins = std::to_string(minutes);
  time.setMessage(mins + ":" + secs, checkTime(minutes));
}

// Changes time text color based on time played
SDL_Color UIManager::checkTime(int minutes) {
  if (minutes < 15) return Parameters::UIManager::goodColor;
  else if (minutes < 20) return Parameters::UIManager::warningColor;
  else return Parameters::UIManager::badColor;
}

// Updates the score based on population
void UIManager::updateTotalScore(PlanetManager *pm, Uint32 elapsedTime) {
  int overtime = elapsedTime - (Parameters::Game::timeLimit);
  if (overtime > 0) {
    overtime *= Parameters::Game::overtimeFactor;
  }
  else {
    overtime = 0;
  }
  
  score = pm->getTotalPopulation() - overtime;
  if (score < 0) score = 0;
  
  
  std::string population = std::to_string(score);
  totalScore.setMessage(population, setTotalScoreColor());

  prevScore = score;
}

// Checks if population is decreasing and changes text color to red
SDL_Color UIManager::setTotalScoreColor() {
  if (prevScore == score)
    return prevColor;
  else if (prevScore < score) {
    prevColor = Parameters::UIManager::goodColor;
    return Parameters::UIManager::goodColor;
  }
  else {
    prevColor = Parameters::UIManager::badColor;
    return Parameters::UIManager::badColor;
  }
}

void UIManager::setSelectedPlanet(Planet p) {
  selectedPlanetInfo.setUiTextures(p);
}

void UIManager::setDockedPlanet(Planet p) {
  DockedPlanetInfo.setUiTextures(p);
}

// Check if mouse click is inside any of the info windows
void UIManager::handleMouseDown(Game::State *gs, PlanetManager *pm) {
  // If mouse button not pressed down, don't check for slider movement
  if (!gs->mouseDown) return;
  
  if (gs->mouseDown) {
    checkClickedArea(gs->clickLocation);
    
    if (currentWindow == currentPlanetWindow)
      checkSliderMovement(&DockedPlanetInfo, gs, pm);
    
    else if (currentWindow == selectedPlanetWindow)
      checkSliderMovement(&selectedPlanetInfo, gs, pm);
  }
}

void UIManager::checkSliderMovement(PlanetInfo *pi, Game::State *gs, PlanetManager *pm) {
  enum {
    neither, fertilitySlider, reserveSlider
  };
  
  // If down, but not dragging, check if slider was clicked
  if (gs->mouseDown && gs->activeSlider == gs->State::inactive) {
    if (pi->checkClick(gs->clickLocation) == fertilitySlider)
      gs->activeSlider = gs->State::resourceSlider;
    
    if (pi->checkClick(gs->clickLocation) == reserveSlider)
      gs->activeSlider = gs->State::depositSlider;
  }
  
  // If so, check mouse movement and adjust slider appropriately
  if (gs->activeSlider != gs->State::inactive) {
    bool movement = pi->moveSlider(gs);
    int percent = pi->getSliderPercent();
    
    if (movement) {
      if (gs->activeSlider == gs->State::resourceSlider) {
        pm->setPlanetMiningPercent(100-percent, currentWindow);
        pm->setPlanetFarmingPercent(percent, currentWindow);
      }
      
      else if (gs->activeSlider == gs->State::depositSlider) {
        pm->setPlanetInfraPercent(100-percent, currentWindow);
        pm->setPlanetReservePercent(percent, currentWindow);
      }
    }
  }
}

void UIManager::checkClickedArea(SDL_Point p) {
  using namespace Parameters::UIManager;
  if ((p.x > currentPlanetRect.x) && (p.x < currentPlanetRect.x + currentPlanetRect.w)
     && (p.y > currentPlanetRect.y) && (p.y < currentPlanetRect.y + currentPlanetRect.h))
    currentWindow = currentPlanetWindow;
  
  else if ((p.x > selectedPlanetRect.x) && (p.x < selectedPlanetRect.x + selectedPlanetRect.w)
          && (p.y > selectedPlanetRect.y) && (p.y < selectedPlanetRect.y + selectedPlanetRect.h))
    currentWindow = selectedPlanetWindow;
  
  else currentWindow = none;
}

// Changes screens during transitions
void UIManager::setActiveScreen(int screen) {
  switch (screen) {
    case menu:
      activeScreen = menu;
      break;
      
    case scores:
      activeScreen = scores;
      break;
      
    case game:
      activeScreen = game;
      break;
      
    case over:
      activeScreen = over;
      break;
      
    case quit:
      activeScreen = quit;
      
    default:
      break;
  }
}

// Special functions to handle ending the game from different screens
void UIManager::setEndGameFlags(int nextScreen, Game::State *gs) {
  if (activeScreen == game) {
    gs->frame = 0;
    gs->gameOver = false;
    gs->endgameFrame = 0;
    gs->endgame = Game::State::none;
    gs->restartGame = true;
    gs->skipMainMenu = true;
    gs->mouseDown = false;
  }
  
  else if (activeScreen == menu) {
    gs->frame = 0;
    gs->gameOver = false;
    gs->endgameFrame = 0;
    gs->endgame = Game::State::none;
    gs->restartGame = true;
    gs->mouseDown = false;
  }
}
