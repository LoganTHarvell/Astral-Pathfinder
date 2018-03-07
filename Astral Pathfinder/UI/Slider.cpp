//
//  Slider.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 3/3/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Slider.hpp"

// MARK: Source Files
#include "Game.hpp"
#include "TextureManager.hpp"

// MARK: - Slider Initialization

void Slider::init(SDL_Rect rectOne, SDL_Rect rectTwo) {
  base = rectOne;
  circle = rectTwo;
  
  bar = nullptr;
  circ = nullptr;
}


// MARK: - Game Loop Methods

void Slider::update() {
  
}

void Slider::render() {
  SDL_RenderCopy(Game::renderer, bar, NULL, &base);
  SDL_RenderCopy(Game::renderer, circ, NULL, &circle);
}

void Slider::clean() {
  if (bar == nullptr || circ == nullptr) return;
  
  if(bar != nullptr) {
    SDL_DestroyTexture(bar);
    bar = nullptr;
  }
  
  if(circ != nullptr) {
    SDL_DestroyTexture(circ);
    circ = nullptr;
  }
}


// MARK: - Slider Methods

bool Slider::isInitialized() {
  if (bar != nullptr && circ != nullptr) return true;
  else return false;
}


void Slider::setTextures(int percent) {
  clean();
  
  bar = TextureManager::loadTexture(SliderParameters::barFilename);
  circ = TextureManager::loadTexture(SliderParameters::circFilename);

  float p = static_cast<float>(percent);
  float scale = base.w/100.0f;
  
  circle.x = static_cast<int>(p*scale)+base.x-(circle.w/2);
}

// TODO: - Separate setting and getting slider position
int Slider::setCirclePosition(int pos) {
  circle.x = pos-(circle.w/2) + base.x;
  int temp = (circle.x+(circle.w/2)) - base.x;
  return static_cast<int>(temp / (base.w/100.0f));
}
