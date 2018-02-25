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
#include "Game.hpp"
#include "TextureManager.hpp"

// MARK: - UIManager Initialization

void UIManager::init() {
  planetInfo.init();
}

// MARK: - Game Loop Methods

void UIManager::update() {
  
}

void UIManager::render() {
  planetInfo.render();
}

// MARK: - UIManager Methods

void UIManager::setText(Planet p) {
  planetInfo.update(p);
}

void UIManager::resetText() {
  planetInfo.resetText();
}
