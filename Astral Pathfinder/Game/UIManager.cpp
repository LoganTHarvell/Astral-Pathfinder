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
  planetInfo.init();
}

// MARK: - Game Loop Methods

void UIManager::update(Game::State *gameState, PlanetManager *planetManager) {
  if (gameState->planetSelected)
    setSelectedPlanet(planetManager->getSelectedPlanet());
  else planetInfo.clean();
  
  // If mouse button not pressed down, don't check for slider movement
  if(!gameState->mouseDown)
    return;
  
  // If down, but not dragging, check if slider was clicked
  if(gameState->mouseDown && !gameState->sliderDrag)
    if(planetInfo.checkClick(gameState))
      gameState->sliderDrag = true;
  
  // If so, check mouse movement and adjust slider appropriately
  if(gameState->sliderDrag) {
    bool movement = planetInfo.moveSlider(gameState);
    int percent = planetInfo.getSliderPercent();
    
    if(movement) {
      planetManager->setPlanetDepoPercent(100-percent);
      planetManager->setPlanetFertPercent(percent);
    }
  }
}

void UIManager::render(Game::State *gameState) {
  if (gameState->planetSelected) planetInfo.render();
}

// MARK: - UIManager Methods

void UIManager::setSelectedPlanet(Planet p) {
  planetInfo.setUiTextures(p);
}

