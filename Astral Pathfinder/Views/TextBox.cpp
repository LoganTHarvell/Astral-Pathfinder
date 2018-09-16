//
//  TextBox.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/24/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  A class for a simple text box UI element that contains a message. Enables
//  intialization, update, and renderering of a collection of text to a screen.

// MARK: Header File
#include "TextBox.hpp"

// MARK: Libraries and Frameworks
#include "TextureManager.hpp"

// MARK: Source Files
#include "Game.hpp"


// MARK: - TextBox Initialization

void TextBox::init(SDL_Rect rectangle) {
  font = TTF_OpenFont(Parameters::UI::TextBox::fontFile.c_str(),
                      Parameters::UI::TextBox::regFontSize);
  
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
// TODO: Take in parameters instead of having methods for each special case

// Default function to give a textbox actual text
void TextBox::setMessage(const std::string words, SDL_Color color) {
  if (texture != nullptr) clean();
  
  SDL_Surface *surface = TTF_RenderText_Solid(font, words.c_str(), color);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

// Fuel textbox text -- calls different TTF render function
void TextBox::setFuelMessage(const std::string words, SDL_Color color) {
  if (texture != nullptr) clean();
  
  SDL_Surface *surface = TTF_RenderText_Blended(font, words.c_str(), color);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

// Sets scores on scoreboard -- same render as fuel but sets rect width to text width
void TextBox::setScoreboardMessage(const std::string words, SDL_Color color) {
  if (texture != nullptr) clean();
  
  int w, h;
  TTF_SizeText(font, words.c_str(), &w, &h);
  
  if (rect.x < Parameters::UI::TextBox::scoreboardLine)
    rect.x = Parameters::UI::TextBox::scoreboardLine - w;
  rect.w = w;
  
  SDL_Surface *surface = TTF_RenderText_Blended(font, words.c_str(), color);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
}

// Sets text for events -- calls wrapped text TTF render
void TextBox::setEventMessage(const std::string words, SDL_Color color) {
  if (texture != nullptr) clean();
  font = TTF_OpenFont(Parameters::UI::TextBox::fontFile.c_str(), Parameters::UI::TextBox::eventFontSize);
  
  int w, h;
  TTF_SizeText(font, words.c_str(), &w, &h);
  rect.h = static_cast<int>(h*2.25);
  
  SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, words.c_str(), color, Parameters::UI::TextBox::wrapLength);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}

// Sets final score on end screen -- matches width and height of text
// Heaviest render function for large but smooth text
void TextBox::setFinalScore(const std::string words) {
  using Parameters::UI::TextBox::color;
  int w, h;
  if (texture != nullptr) clean();
  
  font = TTF_OpenFont(Parameters::UI::TextBox::fontFile.c_str(), Parameters::UI::TextBox::finalScoreFontSize);
  
  TTF_SizeText(font, words.c_str(), &w, &h);
  rect.w = w;
  rect.h = h;
  
  SDL_Surface *surface = TTF_RenderText_Blended(font, words.c_str(), color);
  texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}

// Helper function to check for nullptr
bool TextBox::checkNull() {
  if (texture == nullptr) return true;
  else return false;
}

// Helper function to set x and w values -- cleaner this way
void TextBox::setRect(int x, int w) {
  rect.x = x;
  rect.w = w;
}
