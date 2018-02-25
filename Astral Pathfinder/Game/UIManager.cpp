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

// MARK: Libraries and Frameworks
#include <string>

void UIManager::init() {
  depositsBox.initDeposits();
  fertilityBox.initFertility();
  
  imageRect = {1375, 600, 32, 32};
}

void UIManager::update() {
  
}

void UIManager::render() {
  depositsBox.render();
  fertilityBox.render();
  SDL_RenderCopy(Game::renderer, imageTexture, NULL, &imageRect);
}

void UIManager::setText(int deposits, int fertility) {
  imageTexture = TextureManager::loadTexture("Resources/Assets/planet.png");
  
  std::string depo = "Deposits: " + std::to_string(deposits);
  std::string fert = "Fertility: " + std::to_string(fertility);
  
  depositsBox.setMessage(depo.c_str());
  fertilityBox.setMessage(fert.c_str());
  
}

void UIManager::resetText() {
  depositsBox.reset();
  fertilityBox.reset();
  
  SDL_DestroyTexture(imageTexture);
  imageTexture = nullptr;
}
