//
//  EventsPanel.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 4/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "EventsPanel.hpp"

void EventsPanel::init(SDL_Rect src) {
  using namespace EventPanelParameters;
  texture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, src.w, src.h);
  sample.init({0, 0, 200, 100}); // In reference to texture's coords
  sample.setEventMessage("Hola");
  sample2.init({0, 110, 200, 100}); // In reference to texture's coords
  sample2.setEventMessage("Hi");
  sample3.init({0, 220, 200, 100}); // In reference to texture's coords
  sample3.setEventMessage("Yo");
  sample4.init({0, 330, 200, 100}); // In reference to texture's coords
  sample4.setEventMessage("Sup");
  sample5.init({0, 440, 300, 300}); // In reference to texture's coords
  sample5.setEventMessage("There once was a man named Troy. He lived with his wife Becky... fucking bitch");
}

void EventsPanel::update() {
  
}

void EventsPanel::render(Game::State *gameState) {
  SDL_SetRenderTarget(Game::renderer, texture);
  sample.render(gameState);
  sample2.render(gameState);
  sample3.render(gameState);
  sample4.render(gameState);
  sample5.render(gameState);
  SDL_SetRenderTarget(Game::renderer, NULL);
  SDL_Rect rect = {70, 180, 310, 685};
  SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
}

void EventsPanel::clean() {
  
}
