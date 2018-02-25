//
//  UIManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//


// MARK: Header File
#include "UIManager.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"

void UIManager::init() {
  planetInfo.init();
}

void UIManager::update() {
  
}

void UIManager::render() {
  planetInfo.render();
}

void UIManager::setText(Planet p) {
  planetInfo.setBoxes(p);
}

void UIManager::resetText() {
  planetInfo.resetText();
}
