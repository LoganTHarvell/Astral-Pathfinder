//
//  EndScreen.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

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
  
  // TODO: put clean function in case someone spams endless restarts
  if (texture == nullptr) {
    if (gs->endgame == Game::State::allDiscovered)
      texture = TextureManager::loadTexture(winTextureFile);
    
    else if (gs->endgame == Game::State::noFuel)
      texture = TextureManager::loadTexture(loseTextureFile);
    
    else if (gs->endgame == Game::State::alienAttack)
      texture = TextureManager::loadTexture(alienCrashTextureFile);
  }
}

void EndScreen::render(Game::State *gs) {
  SDL_RenderCopy(Game::renderer, texture, NULL,
                 &Parameters::UIManager::screenRect);
  
  renderButtons(over);
}
