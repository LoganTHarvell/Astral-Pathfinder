//
//  UIManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "UIManager.hpp"

// MARK: Source Files
#include "TextureManager.hpp"

// MARK: - UIManager Initialization

void UIManager::init() {
  using namespace UiParameters;
  selectedPlanetInfo.init(selectedPlanetOrigin);
  DockedPlanetInfo.init(currentPlanetOrigin);
  shipInfo.init(shipInfoOrigin);
  hoverBorder = TextureManager::loadTexture("Resources/Assets/border.png");
}

// MARK: - Game Loop Methods

void UIManager::update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager) {
  // TODO: Implement main menu and endscreen
  if (gameState->mainMenu) {
    checkForHovering(gameState->dragLocation);
    if(gameState->mouseDown)
      checkClickedAreaMainMenu(gameState);
    return;
  }
  else if (gameState->endgame != Game::State::none) {
    gameState->isRunning = false;
    gameState->mainMenu = false;
    return;
  }
  
  shipInfo.clean();
  shipInfo.setText(shipManager->getPlayerShip());
  
  if (gameState->planetSelected) {
    setSelectedPlanet(planetManager->getSelectedPlanet());
    selectedPlanetWindowCleaned = false;
  }
  else if(!selectedPlanetWindowCleaned) {
    selectedPlanetInfo.clean();
    selectedPlanetWindowCleaned = true;
  }
  
  if(planetManager->checkDocked(gameState)) {
    setDockedPlanet(planetManager->getDockedPlanet());
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
  if (gameState->mainMenu) {
    if(mainMenuLabel == startGame)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    else if(mainMenuLabel == scoreboard)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    else if(mainMenuLabel == exitGame)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    return;
  }
  else if (gameState->endgame != Game::State::none) {
    // endScreen.render();
    return;
  }
  
  shipInfo.render();
  if(gameState->planetSelected) selectedPlanetInfo.render(pm->getSelectedPlanet().getPopulation());
  if(gameState->planetCollided) DockedPlanetInfo.render(pm->getDockedPlanet().getPopulation());
}

// MARK: - UIManager Methods

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
        pm->setPlanetDepoPercent(100-percent, currentWindow);
        pm->setPlanetFertPercent(percent, currentWindow);
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
        pm->setPlanetDepoPercent(100-percent, currentWindow);
        pm->setPlanetFertPercent(percent, currentWindow);
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
  if((p.x > currentPlanetOrigin.x) && (p.x < currentPlanetOrigin.x + currentPlanetOrigin.w)
     && (p.y > currentPlanetOrigin.y) && (p.y < currentPlanetOrigin.y + currentPlanetOrigin.h))
    currentWindow = currentPlanetWindow;
  
  else if((p.x > selectedPlanetOrigin.x) && (p.x < selectedPlanetOrigin.x + selectedPlanetOrigin.w)
          && (p.y > selectedPlanetOrigin.y) && (p.y < selectedPlanetOrigin.y + selectedPlanetOrigin.h))
    currentWindow = selectedPlanetWindow;
  
  else currentWindow = none;
}

void UIManager::checkForHovering(SDL_Point p) {
  using namespace UiParameters;
  if((p.x > startGameLabel.x) && (p.x < startGameLabel.x + startGameLabel.w)
     && (p.y > startGameLabel.y) && (p.y < startGameLabel.y + startGameLabel.h)) {
    mainMenuLabel = startGame;
    if(borderRect.y != startGameLabel.y-11)
      borderRect = {582, 390, 460, 95};
  }
  
  else if((p.x > scoreboardLabel.x) && (p.x < scoreboardLabel.x + scoreboardLabel.w)
          && (p.y > scoreboardLabel.y) && (p.y < scoreboardLabel.y + scoreboardLabel.h)) {
    mainMenuLabel = scoreboard;
    if(borderRect.y != scoreboardLabel.y-11)
      borderRect = {582, 527, 460, 96};
  }
  
  else if((p.x > exitGameLabel.x) && (p.x < exitGameLabel.x + exitGameLabel.w)
          && (p.y > exitGameLabel.y) && (p.y < exitGameLabel.y + exitGameLabel.h)) {
    mainMenuLabel = exitGame;
    if(borderRect.y != exitGameLabel.y-11)
      borderRect = {582, 665, 460, 92};
  }
  
  else mainMenuLabel = nothing;
}

void UIManager::checkClickedAreaMainMenu(Game::State *gs) {
  SDL_Point p = gs->clickLocation;
  using namespace UiParameters;
  if((p.x > startGameLabel.x) && (p.x < startGameLabel.x + startGameLabel.w)
     && (p.y > startGameLabel.y) && (p.y < startGameLabel.y + startGameLabel.h)) {
    mainMenuLabel = nothing;
    gs->mainMenu = false;
  }
  
 /* else if((p.x > scoreboardLabel.x) && (p.x < scoreboardLabel.x + scoreboardLabel.w)
          && (p.y > scoreboardLabel.y) && (p.y < scoreboardLabel.y + scoreboardLabel.h))
    mainMenuLabel = nothing; */
  
  if((p.x > exitGameLabel.x) && (p.x < exitGameLabel.x + exitGameLabel.w)
     && (p.y > exitGameLabel.y) && (p.y < exitGameLabel.y + exitGameLabel.h)) {
    mainMenuLabel = nothing;
    gs->mainMenu = false;
    gs->endgame = Game::State::quit;
  }
}
