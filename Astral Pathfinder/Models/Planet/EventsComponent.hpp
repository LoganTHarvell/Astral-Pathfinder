//
//  EventsComponent.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 4/29/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Component class for use in Planet class to manage random events that effect
//  a planets resources.

#ifndef EventsComponent_hpp
#define EventsComponent_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"


class EventsComponent {
public:
  
  // MARK: - Constructors, Destructor
  
  EventsComponent(SDL_Point p);
  ~EventsComponent() = default;
  
  // MARK: - Game Loop Methods
  
  void update(bool blight, bool plague, bool minCollapse, bool popDec, bool overProd);
  
  SDL_Point getLocation() { return location; }
  bool getBlight() { return events.blight; }
  bool getPlague() { return events.plague; }
  bool getMineCollapse() { return events.mineCollapse; }
  bool getPopulationDec() { return events.populationDec; }
  bool getOverProducing() { return events.isOverproducing; }
  bool getTest() { return true; }
  
private:
  
  struct {
    bool isOverproducing;
    bool populationDec;
    bool plague;
    bool blight;
    bool mineCollapse;
  } events;
  
  SDL_Point location;

};


#endif /* EventsComponent_hpp */
