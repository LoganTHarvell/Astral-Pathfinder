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
  planetInfo.init(selectedPlanetOrigin);
}

// MARK: - Game Loop Methods

void UIManager::update(Game::State *gameState, PlanetManager *planetManager) {
  
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
  
  // TODO: Add logic to skip cleaning planet info when already clean
  if (gameState->planetSelected)
    setSelectedPlanet(planetManager->getSelectedPlanet());
  else planetInfo.clean();
  
  
  // TODO: Move mousedown logic to handleMouseDown() helper method
  // handleMouseDown(gameState, planetManager);
  
  // If mouse button not pressed down, don't check for slider movement
  if(!gameState->mouseDown) return;
  
  // If down, but not dragging, check if slider was clicked
  if(gameState->mouseDown && !gameState->sliderOneDrag && !gameState->sliderTwoDrag) {
    if(planetInfo.checkClick(gameState) == 1)
      gameState->sliderOneDrag = true;
    
    if(planetInfo.checkClick(gameState) == 2)
      gameState->sliderTwoDrag = true;
  }
  
  // If so, check mouse movement and adjust slider appropriately
  if(gameState->sliderOneDrag) {
    bool movement = planetInfo.moveSlider(gameState);
    int percent = planetInfo.getSliderPercent();
    
    if(movement) {
      planetManager->setPlanetDepoPercent(100-percent);
      planetManager->setPlanetFertPercent(percent);
    }
  }
  
  if(gameState->sliderTwoDrag) {
    bool movement = planetInfo.moveSlider(gameState);
    int percent = planetInfo.getSliderPercent();
    
    if(movement) {
      planetManager->setPlanetInfraPercent(100-percent);
      planetManager->setPlanetReservePercent(percent);
    }
  }
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
  
  if (gameState->planetSelected) planetInfo.render();
}

// MARK: - UIManager Methods

void UIManager::setSelectedPlanet(Planet p) {
  planetInfo.setUiTextures(p);
}

