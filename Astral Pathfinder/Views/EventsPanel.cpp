//
//  EventsPanel.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 4/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Sub-screen manager for displaying relevant and updated event information.
//  Contains all necessary UI elements and handles their initialization, events,
//  update, and rendering.

// MARK: Header File
#include "EventsPanel.hpp"


// MARK: - PlanetInfo Initialization

void EventsPanel::init() {
  using namespace Parameters::UI::EventPanel;
  texture = SDL_CreateTexture(Game::renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, panelRect.w, panelRect.h);
  src = {0, 0, 310, 700};
  totalHeight = 0;
}


// MARK: - Game Loop Methods

void EventsPanel::update(Game::State *gameState, PlanetManager *pm) {
  checkStatus(pm->getEventsList());
  
  if (gameState->mouseScroll != 0) {
    scrollPanel(gameState->mouseScroll*5);
    gameState->mouseScroll = 0;
  }
}

void EventsPanel::render(Game::State *gameState) {  
  using namespace Parameters::UI::EventPanel;
  SDL_SetRenderTarget(Game::renderer, texture);
  SDL_RenderClear(Game::renderer);
  for (std::vector<TextBox>::reverse_iterator it = eventOrder.rbegin();
      it != eventOrder.rend(); ++it)
    it->render(gameState);
  SDL_SetRenderTarget(Game::renderer, NULL);
  SDL_RenderCopy(Game::renderer, texture, &src, &renderRect);
}


// MARK: - EventsPanel Methods

// Enables scrolling
void EventsPanel::scrollPanel(int scroll) {
  int newY;
  if (scroll < 0) {
    if (totalHeight > Parameters::UI::EventPanel::renderRect.h) {
      newY = src.y + (-scroll);
      if (newY + src.h > totalHeight) src.y = totalHeight - src.h;
      else src.y = newY;
    }
  }
    
  else {
    newY = src.y - scroll;
    if (newY < 0) src.y = 0;
    else src.y = newY;
  }
}

// Checks for planet events and creates/renders appropriate text
void EventsPanel::checkStatus(std::vector<EventsComponent> events) {
  using namespace Parameters::UI::EventPanel;
  
  for (int i = 0; i < events.size(); i++) {
    SDL_Point p = events[i].getLocation();
    updateMap(p, events[i].getBlight(), BLIGHT, outlineColor);
    updateMap(p, events[i].getPlague(), PLAGUE, outlineColor);
    updateMap(p, events[i].getMineCollapse(), MINECOLLAPSE, outlineColor);
    updateMap(p, events[i].getPopulationDec(), POPDEC, popDeclineColor);
    updateMap(p, events[i].getOverProducing(), OVERPROD, overprodColor);
  }
}

// Creates unique key based on planet coords and event happening and checks if in panel
void EventsPanel::updateMap(SDL_Point p, bool flag, int event, SDL_Color color) {
  long key = (static_cast<long>(p.x + event) | (static_cast<long>(p.y + event) << 32));
  
  if (flag) {
    if (map.find(key) == map.end()) {
      TextBox box;
      box.init(Parameters::UI::EventPanel::textBoxesRect);
      box.setEventMessage(createMessage(p, event).c_str(), color);
      box.setKey(key);
      map[key] = box;
      eventOrder.push_back(box);
      updateBoxCoords();
    }
  }
  
  else if (!map.empty()) {
    if (map.find(key) != map.end()) {
      removeFromList(key);
      map[key].clean();
      map.erase(key);
      updateBoxCoords();
    }
  }
}

// Remove event from the list
void EventsPanel::removeFromList(long key) {
  for (int i = 0; i < eventOrder.size(); i++) {
    if (eventOrder[i].getKey() == key) {
      eventOrder[i].clean();
      eventOrder.erase(eventOrder.begin()+i);
      break;
    }
  }
}

// Creates message for each event
std::string EventsPanel::createMessage(SDL_Point p, int event) {
  std::string message;
  
  switch (event) {
    case BLIGHT:
      message = "A blight has occured at ";
      break;
    case PLAGUE:
      message = "A plague is spreading at ";
      break;
    case MINECOLLAPSE:
      message = "The mines collapsed at ";
      break;
    case POPDEC:
      message = "Population is decreasing at ";
      break;
    case OVERPROD:
      message = "Farmers are overproducing at ";
      break;
  }
  
  message += std::to_string(p.x) + "," + std::to_string(p.y);
  
  return message;
}

// Updates the y value of all text boxes in the panel when a new one is added
void EventsPanel::updateBoxCoords() {
  SDL_Rect prev = {0,0,0,0};
  for (std::vector<TextBox>::reverse_iterator it = eventOrder.rbegin();
      it != eventOrder.rend(); ++it) {
    it->setYCoord(prev.y + prev.h + 10);
    prev = it->getRect();
  }
  totalHeight = prev.y + prev.h;
}
