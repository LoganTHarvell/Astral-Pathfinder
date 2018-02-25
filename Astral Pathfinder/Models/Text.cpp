//
//  Text.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/24/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "Text.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include <iostream>
#include <string.h>

using namespace TextParameters;

void Text::initDeposits() {
  font = TTF_OpenFont("Resources/Assets/Arial.ttf", 24);
  
  rect.x = 1275;
  rect.y = 700;
  rect.w = 225;
  rect.h = 50;
}

void Text::initFertility() {
  font = TTF_OpenFont("Resources/Assets/Arial.ttf", 24);
  
  rect.x = 1275;
  rect.y = 750;
  rect.w = 225;
  rect.h = 50;
}

void Text::update() {
  
}

void Text::render() {
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

void Text::setMessage(const char *words) {
  SDL_Surface *surface = TTF_RenderText_Solid(font, words, color);
  
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

void Text::reset() {
  SDL_DestroyTexture(texture);
  texture = nullptr;
}
