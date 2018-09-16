//
//  UIManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Manager class responsible for managing all UI elements, specifically
//  initializing, updating, and rendering. It handles UI elements through
//  groupings into screens and sub-screens that handle their own individual
//  initializing, updating, and rendering.

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

  // TODO: move all gameplay UI elements into a gameplayScreen
  
  // Gameplay UI element initialziation
  time.init(timeRect);
  totalScore.init(totalScoreRect);
  eventsPanel.init();
  finalScore.init({endScoreCoords.x, endScoreCoords.y, 0, 0});
  playerName.init({endNameCoords.x, endNameCoords.y, 0, 0});
  
  // Sub-screens of gameplayScreen
  selectedPlanetInfo.init(selectedPlanetRect);
  DockedPlanetInfo.init(currentPlanetRect);
  shipInfo.init(shipInfoRect);
  
  // Loads gameplayScreen texture
  TextureManager::loadTexture(gameScreenFile, &gameScreen, Game::renderer);
  
  prevScore = 0;
  
  // Initializes Screens
  mainMenu.init();
  scoreboard.init();
  endScreen.init();
  
  if (gameState->skipMainMenu) activeScreen = game;
}


// MARK: - Game Loop Methods

void UIManager::update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager) {
  
  // If user quits, end the game
  if (gameState->endgame == Game::State::quit) {
    gameState->isRunning = false;
  }
  
  // If on the main menu, check game state for button interaction
  else if (activeScreen == menu) {
    mainMenu.checkForHovering(gameState, activeScreen);
    
    if (gameState->mouseDown) {
      int newScreen = mainMenu.checkClick(gameState, activeScreen);
      if (newScreen != -1)
        setActiveScreen(newScreen);
    }
  }
  
  // If on scoreboard, check for button interaction
  else if (activeScreen == scores) {
    scoreboard.checkForHovering(gameState, activeScreen);
    
    if (gameState->mouseDown) {
      int newScreen = scoreboard.checkClick(gameState, activeScreen);
      if (newScreen != -1)
        setActiveScreen(newScreen);
    }
  }
  
  // If at end game screen, enable text input, update endscreen, check clicks
  else if (gameState->gameOver) {
    if (!SDL_IsTextInputActive()) SDL_StartTextInput();
    
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
  
  // During gameplay
  else {
    // Update gameplay UI elements
    updateTime(gameState->elapsedTime);
    updateTotalScore(planetManager, gameState->elapsedTime);
    
    // Update gameplay sub-screens
    eventsPanel.update(gameState, planetManager);
    
    // Update player shipInfo sub-screen when player moves or is docked
    PlayerShip player = shipManager->getPlayerShip();
    if (player.getVelocity().x != 0
        || player.getVelocity().y != 0
        || planetManager->playerIsDocked()) {
      shipInfo.clean();
      shipInfo.setText(player);
    }
    
    // Update selectedPlanetInfo subscreen when a planet is selected
    if (gameState->planetSelected) {
      setSelectedPlanet(planetManager->getSelectedPlanet());
      selectedPlanetWindowCleaned = false;
    }
    else if (!selectedPlanetWindowCleaned) {
      selectedPlanetInfo.clean();
      selectedPlanetWindowCleaned = true;
    }
    
    // Update dockedPlanetInfo subscreen when player is docked
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
  
  if (activeScreen == quit) gameState->endgame = Game::State::quit;
}

void UIManager::render(Game::State *gameState, PlanetManager *pm) {
  using namespace Parameters::UIManager;
  
  // Main Menu Screen
  if (activeScreen == menu) {
    mainMenu.render(gameState);
  }
  
  // Scoreboard Screen
  else if (activeScreen == scores) {
    scoreboard.render(gameState);
  }
  
  // Game Over Screen
  else if (gameState->gameOver && gameState->endgame != Game::State::quit) {
    endScreen.render(gameState);
    
    // Set final score and render
    if (finalScore.checkNull()) {
      finalScore.setFinalScore(std::to_string(score).c_str());
    }
    finalScore.render(gameState);
    
    // Set Player name and render
    if (gameState->renderPlayerName) {
      playerName.setFinalScore(gameState->playerName.c_str());
      gameState->renderPlayerName = false;
    }
    
    playerName.render(gameState);
  }
  
  // Gameplay Screen
  else if (!gameState->gameOver && gameState->endgame != Game::State::quit) {
    SDL_RenderCopy(Game::renderer, gameScreen, NULL,
                   &Parameters::UIManager::screenRect);
  
    // Render gameplayScreen elements
    time.render(gameState);
    totalScore.render(gameState);
    
    // Render sub-screens
    eventsPanel.render(gameState);
    shipInfo.render(gameState);
    
    // If a planet is selected on the map, render selectedPlanetInfo sub-screen
    if (gameState->planetSelected) {
      Planet selectedP = pm->getSelectedPlanet();
      selectedPlanetInfo.render(gameState, selectedP.getPopulation(),
                                selectedP.playerIsDocked());
    }
    // If a player is docked at a planet, render dockedPlanetInfo sub-screen
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
  if (activeScreen == menu || activeScreen == scores) return true;
  return false;
}

// Updates time spent playing
void UIManager::updateTime(Uint32 elapsedTime) {
  
  // Calculates elapsed minutes and seconds, then converts to strings
  int minutes = elapsedTime / 60;
  std::string mins = std::to_string(minutes);
  std::string secs = std::to_string(elapsedTime % 60);
  
  // Sets time text with color set by checkTime return value
  time.setMessage(mins + ":" + secs, checkTime(elapsedTime));

}

// Changes time text color based on time played
SDL_Color UIManager::checkTime(Uint32 elapsedTime) {
  if (elapsedTime < Parameters::Game::timeLimitWarning) {
    return Parameters::UIManager::goodColor;
  }
  else if (elapsedTime < Parameters::Game::timeLimit) {
    return Parameters::UIManager::warningColor;
  }
  else {
    return Parameters::UIManager::badColor;
  }
}

// Updates the score based on population
void UIManager::updateTotalScore(PlanetManager *pm, Uint32 elapsedTime) {
  
  // Calculates overtime
  int overtime = elapsedTime - (Parameters::Game::timeLimit);
  if (overtime > 0) overtime *= Parameters::Game::overtimeFactor;
  else overtime = 0;
  
  // Updates score based on population minus overtime, prevents negative score
  score = pm->getTotalPopulation() - overtime;
  if (score < 0) score = 0;
  
  std::string population = std::to_string(score);
  totalScore.setMessage(population, setTotalScoreColor());

  prevScore = score;

}

// Checks if population is decreasing and changes text color to red
SDL_Color UIManager::setTotalScoreColor() {
  
  if (prevScore == score) {
    return prevColor;
  }
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

// Check for mouse click inside any of the info windows
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
  enum { neither, fertilitySlider, reserveSlider };
  
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
  
  if ((p.x > currentPlanetRect.x)
      && (p.x < currentPlanetRect.x + currentPlanetRect.w)
      && (p.y > currentPlanetRect.y)
      && (p.y < currentPlanetRect.y + currentPlanetRect.h)) {
    currentWindow = currentPlanetWindow;
  }
  else if ((p.x > selectedPlanetRect.x)
           && (p.x < selectedPlanetRect.x + selectedPlanetRect.w)
           && (p.y > selectedPlanetRect.y)
           && (p.y < selectedPlanetRect.y + selectedPlanetRect.h)) {
    currentWindow = selectedPlanetWindow;
  }
  else {
    currentWindow = none;
  }
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
