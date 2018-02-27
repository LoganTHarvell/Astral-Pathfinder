//
//  TextBox.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/24/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "TextBox.hpp"

// MARK: Source Files
#include "Game.hpp"
#include "TextureManager.hpp"


// MARK: - TextBox Initialization

void TextBox::init(SDL_Rect rectangle) {
  font = TTF_OpenFont(TextParameters::fontFile, 36);
  
  rect = rectangle;
}


// MARK: - Game Loop Methods

void TextBox::update() {
  
}

void TextBox::render() {
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}


// MARK: - TextBox Methods

void TextBox::setMessage(const char *words) {
  using TextParameters::color;

  SDL_Surface *surface = TTF_RenderText_Solid(font, words, color);
  
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

void TextBox::clean() {
  if (texture == nullptr) return;
  
  SDL_DestroyTexture(texture);
  texture = nullptr;
}
