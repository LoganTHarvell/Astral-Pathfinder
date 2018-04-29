//
//  EventsPanel.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 4/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "EventsPanel.hpp"
#include <iostream>

void EventsPanel::init() {
  using namespace EventPanelParameters;
  texture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, panelRect.w, panelRect.h);
  src = {0, 0, 310, 700};
  totalHeight = 0;
}

void EventsPanel::update(Game::State *gameState, PlanetManager *pm) {
  checkStatus(pm->getEventsList());
  
  if(gameState->mouseScroll != 0) {
    scrollPanel(gameState->mouseScroll*5);
    gameState->mouseScroll = 0;
  }
}

void EventsPanel::render(Game::State *gameState) {  
  using namespace EventPanelParameters;
  SDL_SetRenderTarget(Game::renderer, texture);
  SDL_RenderClear(Game::renderer);
  if(!map.empty())
    for(auto& p : map)
      p.second.render(gameState);
  SDL_SetRenderTarget(Game::renderer, NULL);
  SDL_RenderCopy(Game::renderer, texture, &src, &renderRect);
}

void EventsPanel::scrollPanel(int scroll) {
  int newY;
  if(scroll < 0) {
    if(totalHeight > EventPanelParameters::renderRect.h) {
      newY = src.y + (-scroll);
      if(newY + src.h > totalHeight) src.y = totalHeight - src.h;
      else src.y = newY;
    }
  }
    
  else {
    newY = src.y - scroll;
    if(newY < 0) src.y = 0;
    else src.y = newY;
  }
}

void EventsPanel::checkStatus(std::vector<EventsComponent> events) {
  using namespace EventPanelParameters;
  changedFlag = false;
  
  for(int i = 0; i < events.size(); i++) {
    SDL_Point p = events[i].getLocation();
    updateMap(p, events[i].getBlight(), BLIGHT, outline);
    updateMap(p, events[i].getPlague(), PLAGUE, outline);
    updateMap(p, events[i].getMineCollapse(), MINECOLLAPSE, outline);
    updateMap(p, events[i].getPopulationDec(), POPDEC, yellow);
    updateMap(p, events[i].getOverProducing(), OVERPROD, red);
  }
  
  if(changedFlag) updateBoxCoords();
}

void EventsPanel::updateMap(SDL_Point p, bool flag, int event, SDL_Color color) {
  long key = (static_cast<long>(p.x + event) | (static_cast<long>(p.y + event) << 32));
  
  if(flag) {
    if(map.find(key) == map.end()) {
      TextBox box;
      box.init(EventPanelParameters::textBoxesRect);
      box.setEventMessage(createMessage(p, event).c_str(), color);
      map[key] = box;
      changedFlag = true;
    }
  }
  
  else if(!map.empty()) {
    if(map.find(key) != map.end()) {
      map[key].clean();
      map.erase(key);
      changedFlag = true;
    }
  }
}

std::string EventsPanel::createMessage(SDL_Point p, int event) {
  std::string message;
  message = "Planet at: " + std::to_string(p.x) + "," + std::to_string(p.y);
  
  switch(event) {
    case BLIGHT:
      message += " undergoing a blight";
      break;
    case PLAGUE:
      message += " is spreading a plague";
      break;
    case MINECOLLAPSE:
      message += " had its mines collapse";
      break;
    case POPDEC:
      message += " has population decreasing";
      break;
    case OVERPROD:
      message += " is overproducing";
      break;
  }
  
  return message;
}

void EventsPanel::updateBoxCoords() {
  SDL_Rect prev = {0,0,0,0};
  for(auto& p : map) {
    p.second.setYCoord(prev.y + prev.h + 10);
    prev = p.second.getRect();
  }
  totalHeight = prev.y + prev.h;
}
