//
//  EndScreen.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Extension of the Screen class for the Endgame screen. Initializes
//  appropriate UI elements and updates them accordingly.

// MARK: Header File
#include "EndScreen.hpp"

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: - EndScreen Initialization

void EndScreen::init() {
  using namespace Parameters::UI::EndScreen;
  
  addButton(over, playAgainButton, playAgainBorder, game);
  addButton(over, mainMenuButton, mainMenuBorder, menu);
}


// MARK: - Game Loop Methods

void EndScreen::update(Game::State *gs) {
  using namespace Parameters::UI::EndScreen;
  
  // TODO: Put clean function in case someone spams endless restarts
  if (texture == nullptr) {
    if (gs->endgame == Game::State::allDiscovered)
      TextureManager::loadTexture(winTextureFile, &texture, Game::renderer);
    
    else if (gs->endgame == Game::State::noFuel)
      TextureManager::loadTexture(loseTextureFile, &texture, Game::renderer);
    
    else if (gs->endgame == Game::State::alienAttack)
      TextureManager::loadTexture(crashTextureFile, &texture, Game::renderer);
  }
}

void EndScreen::render(Game::State *gs) {
  SDL_RenderCopy(Game::renderer, texture, NULL,
                 &Parameters::UIManager::screenRect);
  
  renderButtons(over);
}
