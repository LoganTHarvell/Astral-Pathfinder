//
//  MainMenu.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Extension of the Screen class for the Main Menu screen. Initializes
//  appropriate UI elements and updates them accordingly.

// MARK: Header File
#include "MainMenu.hpp"

// MARK: Parameter File
#include "Parameters.hpp"


// MARK: - MainMenu Initialization

void MainMenu::init() {
  using namespace Parameters::UI::MainMenu;
  
  TextureManager::loadTexture(textureFile, &texture, Game::renderer);
  
  addButton(play, startGameButton, startGameBorder);
  addButton(scores, scoreboardButton, scoreboardBorder);
  addButton(quit, exitGameButton, exitGameBorder);
}


// MARK: - Game Loop Methods

void MainMenu::update(Game::State *gs) {
}

void MainMenu::render(Game::State *gs) {
  SDL_RenderCopy(Game::renderer, texture, NULL,
                 &Parameters::UIManager::screenRect);
  
  renderButtons();
}


// MARK: - MainMenu Methods

// Evaluates buttonID and checks for transitions
Screen::ID MainMenu::getNextScreen(int buttonID) {
  switch (buttonID) {
    case play:
      return ID::game;
    case scores:
      return ID::scores;
    case quit:
      return ID::quit;
      
    default:
      return none;
  }
}
