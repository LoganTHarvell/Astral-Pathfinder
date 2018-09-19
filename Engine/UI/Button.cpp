//
//  Button.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  A UI element that represents a on/off state through a clickable box. This
//  class handles initializing, updating, and rendering the button.

// MARK: Header File
#include "Button.hpp"


// MARK: - Button Initialization

void Button::init(SDL_Rect text, SDL_Rect outline, int id,
                  std::string textureFile, SDL_Renderer *renderer) {
  this->id = id;
  bounds = text;
  border = outline;
  isActive = false;
  
  TextureManager::loadTexture(textureFile, &texture, renderer);
}


// MARK: - Game Loop Methods

void Button::update() {
  
}

void Button::render(SDL_Renderer *renderer) {
  if (isActive)
    SDL_RenderCopy(renderer, texture, NULL, &border);
}


// MARK: - Button Methods

// Modular method for button clicks
bool Button::checkInBounds(SDL_Point p) {
  if ((p.x > bounds.x) && (p.x < bounds.x + bounds.w)
     && (p.y > bounds.y) && (p.y < bounds.y + bounds.h))
    return true;
  
  return false;
}

// Check if mouse is hovering above button
void Button::checkIfHovering(SDL_Point dragLocation) {
  if (checkInBounds(dragLocation))
    isActive = true;
  else
    isActive = false;
}

// Checks if click is within the button bounds
bool Button::checkClick(SDL_Point p) {
  if (checkInBounds(p)) {
    isActive = false;
    return true;
  }
  
  return false;
}
