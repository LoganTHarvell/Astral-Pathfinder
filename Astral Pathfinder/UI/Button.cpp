//
//  Button.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "Button.hpp"
#include "Game.hpp"


// MARK: - Button Initialization

void Button::init(SDL_Rect text, SDL_Rect outline, int screen) {
  bounds = text;
  border = outline;
  isActive = false;
  nextScreen = screen;
}


// MARK: - Game Loop Methods

void Button::update() {
  
}

void Button::render() {
  if (isActive)
    SDL_RenderCopy(Game::renderer, texture, NULL, &border);
}


// MARK: - Button Methods

bool Button::checkInBounds(SDL_Point p) {
  if ((p.x > bounds.x) && (p.x < bounds.x + bounds.w)
     && (p.y > bounds.y) && (p.y < bounds.y + bounds.h))
    return true;
  
  return false;
}

void Button::checkIfHovering(Game::State *gs) {
  if (checkInBounds(gs->dragLocation))
    isActive = true;
  else
    isActive = false;
}

bool Button::checkClick(SDL_Point p) {
  if (checkInBounds(p)) {
    isActive = false;
    return true;
  }
  
  return false;
}
