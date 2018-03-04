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


// MARK: - Slider Methods

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

void Slider::setTextures(Planet p) {
  bar = TextureManager::loadTexture("Resources/Assets/bar.png");
  circ = TextureManager::loadTexture("Resources/Assets/ball.png");

  circle.x = (int)((float)p.getDepositsPercent()*2.65)+base.x-(circle.w/2);
}

int Slider::setCirclePosition(int pos) {
  circle.x = pos-25;
  int temp = (circle.x+25) - base.x;
  return (int)(((float)temp)/2.65);
}
