//
//  TextBox.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/24/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//


// MARKL: Header File
#include "TextBox.hpp"

// MARK: Source Files
#include "Game.hpp"
#include "TextureManager.hpp"

void TextBox::init(SDL_Rect rectangle) {
  font = TTF_OpenFont("Resources/Assets/Arial.ttf", 24);
  
  rect = rectangle;
}

void TextBox::update() {
  
}

void TextBox::render() {
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

void TextBox::setMessage(const char *words) {
  using TextParameters::color;

  SDL_Surface *surface = TTF_RenderText_Solid(font, words, color);
  
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

void TextBox::reset() {
  SDL_DestroyTexture(texture);
  texture = nullptr;
}
