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

void ShipInfo::render() {
  location.render();
  crewLabel.render();
  fuel.render();
  crewNum.render();
  curPlanet.render();
  bar.render();
}

void ShipInfo::clean() {
  location.clean();
  crewLabel.clean();
  fuel.clean();
  crewNum.clean();
  curPlanet.clean();
  bar.clean();
}

// MARK: - ShipInfo Methods

void ShipInfo::setText(Ship ship) {
  SDL_Point pos = ship.getUIPosition();
  std::string loc = "Location: " + std::to_string(pos.x) + "," + std::to_string(pos.y);
  std::string fuelNum = "Fuel: " + std::to_string(ship.getFuel());
  std::string crew = std::to_string(ship.getPopulation());
  
  location.setMessage(loc.c_str());
  fuel.setMessage(fuelNum.c_str());
  crewNum.setMessage(crew.c_str());
  if(crewLabel.checkNull()) {
    crewLabel.setMessage("Crew");
    curPlanet.setMessage("Current Planet: Hoth");
    bar.setMessage("----------------------------------------------------");
  }
}

// MARK: - Helper Methods

void ShipInfo::setUiRects() {
  int buffer = 5; // Small buffer from borders or other elements
  int gapH = 40; // Space between elements
  int midW = origin.x+(origin.w/2); // Midpoint of width
  int threeQuarters = midW+((origin.x+origin.w-midW)/2); // Midpoint between midW and end point
  
  SDL_Point temp = {static_cast<int>(origin.w/4.57), origin.h/4};
  int crewNumW = static_cast<int>(origin.w/6.4);
  int curPlanetW = static_cast<int>(origin.w/1.88);
  
  locationRect = {origin.x+(buffer*2), origin.y+(buffer*2), static_cast<int>(origin.w/2.28), temp.y};
  crewLabelRect = {threeQuarters-(temp.x/2), locationRect.y, temp.x, temp.y};
  fuelRect = {locationRect.x, locationRect.y+gapH, temp.x, temp.y};
  crewNumRect = {threeQuarters-(crewNumW/2), fuelRect.y, crewNumW, temp.y};
  curPlanetRect = {midW-(curPlanetW/2), fuelRect.y+gapH, curPlanetW, static_cast<int>(origin.h/4.8)};
  barRect = {origin.x, curPlanetRect.y-buffer, origin.w, 4};
}
