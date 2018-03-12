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
  locationRect = {1225, 110, 140, 30};
  crewLabelRect = {1420, 110, 70, 30};
  fuelRect = {1225, 150, 70, 30};
  crewNumRect = {1430, 150, 50, 30};
  curPlanetRect = {1290, 190, 170, 25};
  barRect = {1215, 185, 320, 4};
}
