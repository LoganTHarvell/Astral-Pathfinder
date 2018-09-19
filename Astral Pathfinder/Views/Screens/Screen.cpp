//
//  Screen.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Abstract base class for all screens containing essential properties and
//  methods for managing UI elements, and handling some events. Also contains
//  virtual methods to ensure implementation of required game loop methods.

// MARK: Header File
#include "Screen.hpp"

// MARK: Parameter File
#include "Parameters.hpp"


// MARK: - Screen Methods

void Screen::checkForHovering(Game::State *gs) {
  for (Button& b : buttons) b.checkIfHovering(gs->dragLocation);
}

int Screen::checkClick(Game::State *gs) {
  for (Button& b : buttons) {
    if (b.checkClick(gs->clickLocation)) return b.getID();
  }
  
  return -1;
}

void Screen::addButton(int buttonID, SDL_Rect bounds, SDL_Rect border) {
  using namespace Parameters::UI::Button;
  
  Button newButton;
  newButton.init(bounds, border, buttonID, textureFile, Game::renderer);
  
  buttons.push_back(newButton);
}

void Screen::renderButtons() {
  for (Button b : buttons) b.render(Game::renderer);
}
