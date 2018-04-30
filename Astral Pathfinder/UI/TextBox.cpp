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
  font = TTF_OpenFont(TextParameters::fontFile.c_str(), TextParameters::regFontSize);
  
  rect = rectangle;
}


// MARK: - Game Loop Methods

void TextBox::update(Game::State *gs) {
  
}

void TextBox::render(Game::State *gs) {
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

void TextBox::clean() {
  if (texture == nullptr) return;
  
  SDL_DestroyTexture(texture);
  texture = nullptr;
}


// MARK: - TextBox Methods

void TextBox::setMessage(const std::string words, SDL_Color color) {
  if(texture != nullptr) clean();
  
  SDL_Surface *surface = TTF_RenderText_Solid(font, words.c_str(), color);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

void TextBox::setFuelMessage(const std::string words, SDL_Color color) {
  if(texture != nullptr) clean();
  
  SDL_Surface *surface = TTF_RenderText_Blended(font, words.c_str(), color);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

void TextBox::setScoreboardMessage(const std::string words, SDL_Color color) {
  if(texture != nullptr) clean();
  
  int w, h;
  TTF_SizeText(font, words.c_str(), &w, &h);
  
  if(rect.x < TextParameters::scoreboardLine)
    rect.x = TextParameters::scoreboardLine - w;
  rect.w = w;
  
  SDL_Surface *surface = TTF_RenderText_Blended(font, words.c_str(), color);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

void TextBox::setEventMessage(const std::string words, SDL_Color color) {
  if(texture != nullptr) clean();
  font = TTF_OpenFont(TextParameters::fontFile.c_str(), TextParameters::eventFontSize);
  
  int w, h;
  TTF_SizeText(font, words.c_str(), &w, &h);
  rect.h = static_cast<int>(h*2.25);
  
  SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, words.c_str(), color, TextParameters::wrapLength);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}

void TextBox::setFinalScore(const std::string words) {
  using TextParameters::color;
  int w, h;
  if(texture != nullptr) clean();
  
  font = TTF_OpenFont(TextParameters::fontFile.c_str(), TextParameters::finalScoreFontSize);
  
  TTF_SizeText(font, words.c_str(), &w, &h);
  rect.w = w;
  rect.h = h;
  
  SDL_Surface *surface = TTF_RenderText_Blended(font, words.c_str(), color);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}

bool TextBox::checkNull() {
  if(texture == nullptr) return true;
  else return false;
}

void TextBox::setRect(int x, int w) {
  rect.x = x;
  rect.w = w;
}
