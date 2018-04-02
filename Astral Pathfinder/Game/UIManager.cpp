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

// MARK: Source Files
#include "TextureManager.hpp"

// MARK: - UIManager Initialization

void UIManager::init() {
  using namespace UiParameters;
  
  time.init(timeRect);
  selectedPlanetInfo.init(selectedPlanetRect);
  DockedPlanetInfo.init(currentPlanetRect);
  shipInfo.init(shipInfoRect);
}

// MARK: - Game Loop Methods

void UIManager::update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager) {
  // TODO: Implement main menu and endscreen
  if (gameState->mainMenu) {
    // mainMenu.update(gameState);
    return;
  }
  else if (gameState->endgame != Game::State::none) {
    // endScreen.update(gameState);
    gameState->isRunning = false;
    return;
  }
  
  updateTime(gameState->elapsedTime);
  
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
  
  if(planetManager->planetIsDocked()) {
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
  if (gameState->mainMenu) {
    // mainMenu.render();
    return;
  }
  else if (gameState->endgame != Game::State::none) {
    // endScreen.render();
    return;
  }
  
  time.render(gameState);
  shipInfo.render(gameState);
  
  if(gameState->planetSelected) {
    int selectedPop = pm->getSelectedPlanet().getPopulation();
    selectedPlanetInfo.render(gameState, selectedPop);
  }
  if(gameState->planetCollided) {
    int dockedPop = pm->getDockedPlanet().getPopulation();
    DockedPlanetInfo.render(gameState, dockedPop);
  }
}

// MARK: - UIManager Methods

void UIManager::updateTime(Uint32 elapsedTime) {
  std::string secs = std::to_string(elapsedTime % 60);
  std::string mins = std::to_string(elapsedTime / 60);
  
  time.setMessage("Time " + mins + ":" + secs);
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
