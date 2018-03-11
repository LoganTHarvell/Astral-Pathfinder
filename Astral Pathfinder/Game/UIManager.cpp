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
  
  // TODO: Add logic to skip cleaning planet info when already clean
  if (gameState->planetSelected)
    setSelectedPlanet(planetManager->getSelectedPlanet());
  else {selectedPlanetInfo.clean(); currentPlanetInfo.clean();}
  
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
  if (gameState->planetSelected) {selectedPlanetInfo.render(); currentPlanetInfo.render();}
}

// MARK: - UIManager Methods

void UIManager::setSelectedPlanet(Planet p) {
  selectedPlanetInfo.setUiTextures(p);
  currentPlanetInfo.setUiTextures(p);
}

void UIManager::handleMouseDown(Game::State *gs, PlanetManager *pm) {
  // If mouse button not pressed down, don't check for slider movement
  if(!gs->mouseDown) return;
  
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
      pm->setPlanetDepoPercent(100-percent);
      pm->setPlanetFertPercent(percent);
    }
  }
  
  if(gs->activeSlider == gs->State::selectTwo) {
    bool movement = selectedPlanetInfo.moveSlider(gs);
    int percent = selectedPlanetInfo.getSliderPercent();
    
    if(movement) {
      pm->setPlanetInfraPercent(100-percent);
      pm->setPlanetReservePercent(percent);
    }
  }
}
