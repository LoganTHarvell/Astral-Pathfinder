//
//  PlanetInfo.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/25/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "PlanetInfo.hpp"

// MARK: Libraries and Frameworks
#include <string>

// MARK: - PlanetInfo Initialization

void PlanetInfo::init() {
  using namespace InfoParameters;
  depositsText.init(depositsRect);
  fertilityText.init(fertilityRect);
}

// MARK: - Game Loop Methods

void PlanetInfo::update() {
  
}

void PlanetInfo::render() {
  depositsText.render();
  fertilityText.render();
}

// MARK: - PlanetInfo Methods

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
