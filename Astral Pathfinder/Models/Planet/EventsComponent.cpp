//
//  EventsComponent.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 4/29/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "EventsComponent.hpp"


// MARK: - Constructor

EventsComponent::EventsComponent(SDL_Point p) {
  location = p;
}


// MARK: - Game Loop Methods

void EventsComponent::update(bool blight, bool plague, bool minCollapse, bool popDec, bool overProd) {
  events.blight = blight;
  events.plague = plague;
  events.populationDec = popDec;
  events.mineCollapse = minCollapse;
  events.isOverproducing = overProd;
}
