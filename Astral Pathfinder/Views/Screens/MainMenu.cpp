//
//  MainMenu.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "MainMenu.hpp"


// MARK: - MainMenu Initialization

void MainMenu::init() {
  using namespace MainMenuParameters;
  
  texture = TextureManager::loadTexture("../Resources/mainMenu.png");
  
  addButton(menu, startGameButton, startGameBorder, game);
  addButton(menu, scoreboardButton, scoreboardBorder, scores);
  addButton(menu, exitGameButton, exitGameBorder, quit);
}


// MARK: - Game Loop Methods

void MainMenu::update(Game::State *gs) {
}

void MainMenu::render(Game::State *gs) {
  SDL_RenderCopy(Game::renderer, texture, NULL,
                 &Parameters::UIManager::screenRect);
  
  renderButtons(menu);
}
