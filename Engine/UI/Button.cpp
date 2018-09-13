//
//  Button.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Button.hpp"


// MARK: - Button Initialization

void Button::init(SDL_Rect text, SDL_Rect outline, int screen,
                  std::string textureFile, SDL_Renderer *renderer) {
  bounds = text;
  border = outline;
  isActive = false;
  nextScreen = screen;
  
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
