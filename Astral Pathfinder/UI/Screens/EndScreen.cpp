//
//  EndScreen.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "EndScreen.hpp"

void EndScreen::init() {
  
}

void EndScreen::update(Game::State *gs) {
  // TODO: put clean function in case someone spams endless restarts
  if(texture == nullptr) {
    if(gs->endgame == Game::State::allDiscovered)
      texture = TextureManager::loadTexture("../Resources/winScreen.png");
    
    else if(gs->endgame == Game::State::noFuel)
      texture = TextureManager::loadTexture("../Resources/loseScreen.png");
    
    else if(gs->endgame == Game::State::alienAttack)
      texture = TextureManager::loadTexture("../Resources/alienScreen.png");
  }
}

void EndScreen::render(Game::State *gs) {
  SDL_RenderCopy(Game::renderer, texture, NULL, &ScreenParameters::screenRect);
  
  if(borderRect.y != 0)
    SDL_RenderCopy(Game::renderer, hoveringBorder, NULL, &borderRect);
}

void EndScreen::checkForHovering(Game::State *gs) {
  using namespace EndScreenParameters;
  SDL_Point p = gs->dragLocation;
  
  if((p.x > playAgainButton.x) && (p.x < playAgainButton.x + playAgainButton.w)
     && (p.y > playAgainButton.y) && (p.y < playAgainButton.y + playAgainButton.h))
      borderRect = playAgainBorder;
  
  else if((p.x > mainMenuButton.x) && (p.x < mainMenuButton.x + mainMenuButton.w)
          && (p.y > mainMenuButton.y) && (p.y < mainMenuButton.y + mainMenuButton.h))
      borderRect = mainMenuBorder;
  
  else borderRect = {};
}

int EndScreen::checkClick(Game::State *gs) {
  using namespace EndScreenParameters;
  SDL_Point p = gs->clickLocation;
  borderRect = {};
  
  if((p.x > playAgainButton.x) && (p.x < playAgainButton.x + playAgainButton.w)
     && (p.y > playAgainButton.y) && (p.y < playAgainButton.y + playAgainButton.h)) {
    gs->frame = 0;
    gs->gameOver = false;
    gs->endgameFrame = 0;
    gs->endgame = Game::State::none;
    gs->restartGame = true;
    gs->skipMainMenu = true;
    gs->mouseDown = false;
    return activeScreen::game;
  }
  
  else if((p.x > mainMenuButton.x) && (p.x < mainMenuButton.x + mainMenuButton.w)
          && (p.y > mainMenuButton.y) && (p.y < mainMenuButton.y + mainMenuButton.h)) {
    gs->frame = 0;
    gs->gameOver = false;
    gs->endgameFrame = 0;
    gs->endgame = Game::State::none;
    gs->restartGame = true;
    gs->mouseDown = false;
    return activeScreen::menu;
  }
  
  return activeScreen::none;
}
