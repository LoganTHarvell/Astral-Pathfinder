//
//  ShipInfo.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 3/11/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Sub-screen manager for displaying relevant and updated ship information.
//  Contains all necessary UI elements and handles their initialization, events,
//  update, and rendering.

#ifndef ShipInfo_hpp
#define ShipInfo_hpp

// MARK: Source Files
#include "PlayerShip.hpp"
#include "TextBox.hpp"


// MARK: - ShipInfo Class

class ShipInfo {

public:
  
  // MARK: - ShipInfo Initialization
  
  void init(SDL_Rect src);
  
  // MARK: - Game Loop Methods
  
  void render(Game::State *gs);
  void clean();
  
  // MARK: - ShipInfo Methods
  
  void setText(PlayerShip ship);
  
private:
  
  // MARK: - ShipInfo Fields
  
  TextBox location, crewLabel, crewNum, fuel, curPlanet, bar;
  SDL_Rect locationRect, crewLabelRect, crewNumRect, fuelRect,
           curPlanetRect, barRect, origin;
  
  // MARK: - Helper Methods
  
  void setUiRects();

};

#endif /* ShipInfo_hpp */
