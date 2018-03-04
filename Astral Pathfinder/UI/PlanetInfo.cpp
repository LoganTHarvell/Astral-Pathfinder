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
#include <iostream>
#include "Map.hpp"


// MARK: - PlanetInfo Initialization

void PlanetInfo::init() {
  using namespace InfoParameters;
  depositsText.init(depositsRect);
  fertilityText.init(fertilityRect);
  slider.init(slideBase, circle);
}


// MARK: - Game Loop Methods

void PlanetInfo::render() {
  depositsText.render();
  fertilityText.render();
  slider.render();
}

void PlanetInfo::clean() {
  depositsText.clean();
  fertilityText.clean();
  slider.clean();
}


// MARK: - PlanetInfo Methods

void PlanetInfo::setText(Planet p) {
  setBoxes(p);
  slider.setTextures();
}

bool PlanetInfo::checkClick(Game::State *gameState) {
  int x = gameState->clickLocation.x;
  int y = gameState->clickLocation.y;
  SDL_Rect temp = slider.getCirclePosition();
  if((x > temp.x) && (x < temp.x + temp.w)
     && (y > temp.y) && (y < temp.y + temp.h))
    return true;
  
  return false;
}

void PlanetInfo::moveSlider(Game::State *gameState) {
  int x = gameState->dragLocation.x;
  SDL_Rect temp = slider.getBasePosition();
  if((x > temp.x) && (x < temp.x + temp.w)) {
    slider.setCirclePosition(x);
  }
}

// MARK: - Helper Methods

void PlanetInfo::setBoxes(Planet p) {
  std::string depo = "Deposits: " + std::to_string(p.getDeposits());
  std::string fert = "Fertility: " + std::to_string(p.getFertility());
  
  depositsText.setMessage(depo.c_str());
  fertilityText.setMessage(fert.c_str());
}

