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
  dpText.init(depositsPercentRect);
  fpText.init(fertilityPercentRect);
  mining.init(miningLabel);
  farming.init(farmingLabel);
  slider.init(slideBase, circle);
}


// MARK: - Game Loop Methods

void PlanetInfo::render() {
  depositsText.render();
  fertilityText.render();
  dpText.render();
  fpText.render();
  mining.render();
  farming.render();
  slider.render();
}

void PlanetInfo::clean() {
  depositsText.clean();
  fertilityText.clean();
  dpText.clean();
  fpText.clean();
  mining.clean();
  farming.clean();
  slider.clean();
}


// MARK: - PlanetInfo Methods

void PlanetInfo::setText(Planet p) {
  setBoxes(p);
  slider.setTextures(p.getFertilityPercent());
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

int PlanetInfo::moveSlider(Game::State *gameState) {
  int x = gameState->dragLocation.x;
  SDL_Rect temp = slider.getBasePosition();
  
  if((x > temp.x) && (x < temp.x + temp.w + 1)) {
    int p = slider.setCirclePosition(x);
    setNewPercent(p);
    return p;
  }
  
  return -1;
}

// MARK: - Helper Methods

void PlanetInfo::setBoxes(Planet p) {
  std::string depo = "Deposits: " + setSpaces(p.getDeposits()) + std::to_string(p.getDeposits());
  std::string fert = "Fertility: " + setSpaces(p.getFertility()) + std::to_string(p.getFertility());
  std::string depoPercent = setSpaces(p.getDepositsPercent()) + std::to_string(p.getDepositsPercent()) + "%";
  std::string fertPercent = setSpaces(p.getFertilityPercent()) + std::to_string(p.getFertilityPercent()) + "%";
  
  depositsText.setMessage(depo.c_str());
  fertilityText.setMessage(fert.c_str());
  dpText.setMessage(depoPercent.c_str());
  fpText.setMessage(fertPercent.c_str());
  mining.setMessage("Mining");
  farming.setMessage("Farming");
}

void PlanetInfo::setNewPercent(int p) {
  std::string depoPercent = setSpaces(100-p) + std::to_string(100-p) + "%";
  dpText.setMessage(depoPercent.c_str());
  
  std::string fertPercent = setSpaces(p) + std::to_string(p) + "%";
  fpText.setMessage(fertPercent.c_str());
}

std::string PlanetInfo::setSpaces(int p) {
  std::string s;
  
  if(p >= 0 && p < 10)
    s = s + " " + " ";
  else if(p >= 10 && p < 100)
    s = s + " ";
  
  return s;
}
