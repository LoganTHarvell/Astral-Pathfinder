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
  using namespace UiParamters;
  selectedPlanetInfo.init(selectedPlanetOrigin);
  currentPlanetInfo.init(currentPlanetOrigin);
  shipInfo.init(shipInfoOrigin);
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
  
  shipInfo.clean();
  shipInfo.setText(shipManager->getPlayerShip());
  
  if (gameState->planetSelected) {
    setSelectedPlanet(planetManager->getSelectedPlanet());
    twoClean = false;
  }
  else if(!twoClean) {
    selectedPlanetInfo.clean();
    twoClean = true;
  }
  
  if(planetManager->checkDocked(gameState)) {
    setCurrentPlanet(planetManager->getCurrentPlanet());
    oneClean = false;
  }
  else if(!oneClean) {
    currentPlanetInfo.clean();
    oneClean = true;
  }
  
  handleMouseDown(gameState, planetManager);
}

void UIManager::render(Game::State *gameState) {
  if (gameState->mainMenu) {
    // mainMenu.render();
    return;
  }
  else if (gameState->endgame != Game::State::none) {
    // endScreen.render();
    return;
  }
  
  shipInfo.render();
  if(gameState->planetSelected) selectedPlanetInfo.render();
  if(gameState->planetCollided) currentPlanetInfo.render();
}

// MARK: - UIManager Methods

void UIManager::setSelectedPlanet(Planet p) {
  selectedPlanetInfo.setUiTextures(p);
}

void UIManager::setCurrentPlanet(Planet p) {
  currentPlanetInfo.setUiTextures(p);
}

void UIManager::handleMouseDown(Game::State *gs, PlanetManager *pm) {
  // If mouse button not pressed down, don't check for slider movement
  if(!gs->mouseDown) return;
  
  if(gs->mouseDown)
    window = checkClickedArea(gs->clickLocation);
  
  // Current Planet Window
  if(window == 1) {
    // If down, but not dragging, check if slider was clicked
    if(gs->mouseDown && gs->activeSlider == gs->State::inactive) {
      if(currentPlanetInfo.checkClick(gs->clickLocation) == 1)
        gs->activeSlider = gs->State::currentOne;
      
      if(currentPlanetInfo.checkClick(gs->clickLocation) == 2)
        gs->activeSlider = gs->State::currentTwo;
    }
  
    // If so, check mouse movement and adjust slider appropriately
    if(gs->activeSlider == gs->State::currentOne) {
      bool movement = currentPlanetInfo.moveSlider(gs);
      int percent = currentPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetDepoPercent(100-percent, window);
        pm->setPlanetFertPercent(percent, window);
      }
    }
  
    if(gs->activeSlider == gs->State::currentTwo) {
      bool movement = currentPlanetInfo.moveSlider(gs);
      int percent = currentPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetInfraPercent(100-percent, window);
        pm->setPlanetReservePercent(percent, window);
      }
    }
  }
  
  // Selected Planet Window
  if(window == 2) {
    // If down, but not dragging, check if slider was clicked
    if(gs->mouseDown && gs->activeSlider == gs->State::inactive) {
      if(selectedPlanetInfo.checkClick(gs->clickLocation) == 1)
        gs->activeSlider = gs->State::selectOne;
      
      if(selectedPlanetInfo.checkClick(gs->clickLocation) == 2)
        gs->activeSlider = gs->State::selectTwo;
    }
    
    // If so, check mouse movement and adjust slider appropriately
    if(gs->activeSlider == gs->State::selectOne) {
      bool movement = selectedPlanetInfo.moveSlider(gs);
      int percent = selectedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetDepoPercent(100-percent, window);
        pm->setPlanetFertPercent(percent, window);
      }
    }
    
    if(gs->activeSlider == gs->State::selectTwo) {
      bool movement = selectedPlanetInfo.moveSlider(gs);
      int percent = selectedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetInfraPercent(100-percent, window);
        pm->setPlanetReservePercent(percent, window);
      }
    }
  }
}

int UIManager::checkClickedArea(SDL_Point p) {
  using namespace UiParamters;
  if((p.x > currentPlanetOrigin.x) && (p.x < currentPlanetOrigin.x + currentPlanetOrigin.w)
     && (p.y > currentPlanetOrigin.y) && (p.y < currentPlanetOrigin.y + currentPlanetOrigin.h))
    return 1;
  
  else if((p.x > selectedPlanetOrigin.x) && (p.x < selectedPlanetOrigin.x + selectedPlanetOrigin.w)
          && (p.y > selectedPlanetOrigin.y) && (p.y < selectedPlanetOrigin.y + selectedPlanetOrigin.h))
    return 2;
  
  else return -1;
}
