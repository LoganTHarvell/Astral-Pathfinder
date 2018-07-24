//
//  MainMenu.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "MainMenu.hpp"

void MainMenu::init() {
  texture = TextureManager::loadTexture("../Resources/mainMenu.png");
}

void MainMenu::update(Game::State *gs) {
  
}

void MainMenu::render(Game::State *gs) {
  
  SDL_RenderCopy(Game::renderer, texture, NULL, &ScreenParameters::screenRect);
  
  if(borderRect.y != 0)
    SDL_RenderCopy(Game::renderer, hoveringBorder, NULL, &borderRect);
}

void MainMenu::checkForHovering(Game::State *gs) {
  using namespace MainMenuParameters;
  SDL_Point p = gs->dragLocation;
  
  if((p.x > startGameButton.x) && (p.x < startGameButton.x + startGameButton.w)
     && (p.y > startGameButton.y) && (p.y < startGameButton.y + startGameButton.h))
      borderRect = startGameBorder;
  
  else if((p.x > scoreboardButton.x) && (p.x < scoreboardButton.x + scoreboardButton.w)
          && (p.y > scoreboardButton.y) && (p.y < scoreboardButton.y + scoreboardButton.h))
      borderRect = scoreboardBorder;
  
  else if((p.x > exitGameButton.x) && (p.x < exitGameButton.x + exitGameButton.w)
          && (p.y > exitGameButton.y) && (p.y < exitGameButton.y + exitGameButton.h))
      borderRect = exitGameBorder;
  
  else borderRect = {};
}

int MainMenu::checkClick(Game::State *gs) {
  using namespace MainMenuParameters;
  SDL_Point p = gs->clickLocation;
  borderRect = {};
  
  if((p.x > startGameButton.x) && (p.x < startGameButton.x + startGameButton.w)
     && (p.y > startGameButton.y) && (p.y < startGameButton.y + startGameButton.h)) {
    gs->planetSelected = false;
    return activeScreen::game;
  }
  
  else if((p.x > scoreboardButton.x) && (p.x < scoreboardButton.x + scoreboardButton.w)
          && (p.y > scoreboardButton.y) && (p.y < scoreboardButton.y + scoreboardButton.h))
    return activeScreen::scores;
  
  else if((p.x > exitGameButton.x) && (p.x < exitGameButton.x + exitGameButton.w)
          && (p.y > exitGameButton.y) && (p.y < exitGameButton.y + exitGameButton.h))
    gs->endgame = Game::State::quit;
  
  return activeScreen::none;
}
