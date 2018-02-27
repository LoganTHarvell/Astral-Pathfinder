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
  
}

void UIManager::render(Game::State *gameState) {
  if (gameState->planetSelected) planetInfo.render();
}

// MARK: - UIManager Methods

void UIManager::setSelectedPlanet(Planet p) {
  planetInfo.setText(p);
}

