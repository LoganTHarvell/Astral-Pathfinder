//
//  Screen.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "Screen.hpp"

void Screen::checkForHovering(Game::State *gs, int screen) {
  for(Button& b : *getActiveScreenButtons(screen))
    b.checkIfHovering(gs);
}

int Screen::checkClick(Game::State *gs, int screen) {
  for(Button& b : *getActiveScreenButtons(screen))
    if(b.checkClick(gs->clickLocation))
      return b.getNextScreen();
  
  return -1;
}

void Screen::addButton(int currentScreen, SDL_Rect bounds, SDL_Rect border, int nextScreen) {
  Button newButton;
  newButton.init(bounds, border, nextScreen);
  
  getActiveScreenButtons(currentScreen)->push_back(newButton);
}

void Screen::renderButtons(int screen) {
  for(Button b : *getActiveScreenButtons(screen)) b.render();
}

std::vector<Button> *Screen::getActiveScreenButtons(int screen) {
  using namespace ScreenParameters;
  
  switch(screen) {
    case menu:
      return &mainMenuButtons;
      break;
      
    case scores:
      return &scoreboardButtons;
      break;
      
    case over:
      return &endScreenButtons;
      break;
      
    default:
      break;
  }
  
  return {};
}
