//
//  ShipInfo.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 3/11/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "ShipInfo.hpp"

// MARK: Libraries and Frameworks
#include <string>

// MARK: - ShipInfo Initialization

void ShipInfo::init(SDL_Rect src) {
  origin = src;
  setUiRects();
  
  location.init(locationRect);
  crewLabel.init(crewLabelRect);
  fuel.init(fuelRect);
  crewNum.init(crewNumRect);
  curPlanet.init(curPlanetRect);
  bar.init(barRect);
}


// MARK: - Game Loop Methods

void ShipInfo::render(Game::State *gs) {
  location.render(gs);
  crewLabel.render(gs);
  fuel.render(gs);
  crewNum.render(gs);
  curPlanet.render(gs);
  bar.render(gs);
}

void ShipInfo::clean() {
  location.clean();
  fuel.clean();
  curPlanet.clean();
}

// MARK: - ShipInfo Methods

void ShipInfo::setText(PlayerShip ship) {
  SDL_Point pos = ship.mapPosition();
  int fuelAmount = ship.getFuel();
  std::string loc = "Location: " + std::to_string(pos.x) + "," + std::to_string(pos.y);
  std::string fuelNum = "Fuel: " + std::to_string(fuelAmount);
  
  if (fuelAmount < 250) fuel.setFuelMessage(fuelNum.c_str(), {128,0,0});
  else fuel.setFuelMessage(fuelNum.c_str());
  location.setMessage(loc.c_str());
  curPlanet.setMessage("Current Planet");
  if (crewLabel.checkNull()) {
    crewLabel.setMessage("Crew");
    crewNum.setMessage(std::to_string(Parameters::Ship::totalCrew));
    bar.setMessage("----------------------------------------------------");
  }
}

// MARK: - Helper Methods

void ShipInfo::setUiRects() {
  // TODO: clean this up
  int buffer = 5; // Small buffer from borders or other elements
  int gapH = 40; // Space between elements
  int midW = origin.x+(origin.w/2); // Midpoint of width
  
  SDL_Point temp = {static_cast<int>(origin.w/4.57), origin.h/4};
  int crewNumW = static_cast<int>(origin.w/6.4);
  int curPlanetW = static_cast<int>(origin.w/1.88);
  int crewNumX = (temp.x-crewNumW)/2;
  
  
  crewLabelRect = {origin.x+temp.y, origin.y+(buffer*2), temp.x, temp.y};
  locationRect = {midW-(buffer*4), crewLabelRect.y, static_cast<int>(origin.w/2), temp.y};
  fuelRect = {locationRect.x+(temp.x/2), locationRect.y+gapH, temp.x+(buffer*4), temp.y};
  crewNumRect = {crewLabelRect.x+crewNumX, fuelRect.y, crewNumW, temp.y};
  curPlanetRect = {midW-(curPlanetW/2), fuelRect.y+gapH, curPlanetW, static_cast<int>(origin.h/4.8)};
  barRect = {origin.x, curPlanetRect.y-6, origin.w, 5};
}
