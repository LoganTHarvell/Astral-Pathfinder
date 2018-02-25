//
//  PlanetInfo.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/25/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "PlanetInfo.hpp"
#include <string>
#include "TextBox.hpp"
void PlanetInfo::init() {
  SDL_Rect temp = {1275, 600, 225, 50};
  depositsText.init(temp);
  
  temp = {1275, 650, 225, 50};
  fertilityText.init(temp);
}

void PlanetInfo::update() {
  
}

void PlanetInfo::render() {
  depositsText.render();
  fertilityText.render();
}

void PlanetInfo::setBoxes(Planet p) {
  std::string depo = "Deposits: " + std::to_string(p.getDeposits());
  std::string fert = "Fertility: " + std::to_string(p.getFertility());
  
  depositsText.setMessage(depo.c_str());
  fertilityText.setMessage(fert.c_str());
}

void PlanetInfo::resetText() {
  depositsText.reset();
  fertilityText.reset();
}
