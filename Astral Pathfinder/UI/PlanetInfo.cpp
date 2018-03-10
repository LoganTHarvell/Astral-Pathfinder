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

void PlanetInfo::init(SDL_Rect src) {
  origin = src;
  setUiRects();
  
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

void PlanetInfo::setUiTextures(Planet p) {
  setBoxes(p);
  
  if (slider.isInitialized()) {
    // Sets correct slider position for given planet
    float ratio = p.getFertilityPercent()/100.0f;
    SDL_Rect tmpR = slider.getBaseRect();
    slider.setSliderPosition(static_cast<int>(tmpR.w * ratio));
  }
  // Sets slider textures if not initialized
  else slider.setTextures(p.getFertilityPercent());

  
}

bool PlanetInfo::checkClick(Game::State *gameState) {
  int x = gameState->clickLocation.x;
  int y = gameState->clickLocation.y;
  SDL_Rect temp = slider.getSliderRect();
  if((x > temp.x) && (x < temp.x + temp.w)
     && (y > temp.y) && (y < temp.y + temp.h))
    return true;
  
  return false;
}

bool PlanetInfo::moveSlider(Game::State *gameState) {
  SDL_Rect temp = slider.getBaseRect();
  int x = gameState->dragLocation.x - temp.x;
  
  if((x > 0) && (x < temp.w + 1)) {
    slider.setSliderPosition(x);
    setNewPercentText();
    return true;
  }
  return false;
}

// MARK: - Helper Methods

void PlanetInfo::setBoxes(Planet p) {
  std::string depo = "Deposits: " + setStringSpaces(p.getDeposits()) + std::to_string(p.getDeposits());
  std::string fert = "Fertility: " + setStringSpaces(p.getFertility()) + std::to_string(p.getFertility());
  std::string depoPercent = setStringSpaces(p.getDepositsPercent()) + std::to_string(p.getDepositsPercent()) + "%";
  std::string fertPercent = setStringSpaces(p.getFertilityPercent()) + std::to_string(p.getFertilityPercent()) + "%";
  
  depositsText.setMessage(depo.c_str());
  fertilityText.setMessage(fert.c_str());
  dpText.setMessage(depoPercent.c_str());
  fpText.setMessage(fertPercent.c_str());
  mining.setMessage("Mining");
  farming.setMessage("Farming");
}

void PlanetInfo::setNewPercentText() {
  int p = getSliderPercent();
  
  std::string depoPercent = setStringSpaces(100-p) + std::to_string(100-p) + "%";
  dpText.setMessage(depoPercent.c_str());
  
  std::string fertPercent = setStringSpaces(p) + std::to_string(p) + "%";
  fpText.setMessage(fertPercent.c_str());
}

// Creates buffer with spaces for displayed numbers on UI so textboxes don't adjust
std::string PlanetInfo::setStringSpaces(int p) {
  std::string s;
  
  if(p >= 0 && p < 10)
    s = s + " " + " ";
  else if(p >= 10 && p < 100)
    s = s + " ";
  
  return s;
}

void PlanetInfo::setUiRects() {
  int leftBuffer = origin.x+10;
  int topBuffer = origin.y+10;
  int midW = origin.x + (origin.w/2);
  
  depositsRect = {leftBuffer, topBuffer, 135, 35};
  fertilityRect = {midW+10, topBuffer, 135, 35};
  miningLabel = {leftBuffer, depositsRect.y+50, 75, 30};
  depositsPercentRect = {miningLabel.x+(miningLabel.w/2)-25, miningLabel.y+40, 50, 25};
  slideBase = {leftBuffer+miningLabel.w+15, miningLabel.y+20, 125, 15};
  circle = {NULL, slideBase.y-6, 25, 25};
  farmingLabel = {slideBase.x+slideBase.w+15, miningLabel.y, 75, 30};
  fertilityPercentRect = {farmingLabel.x+(farmingLabel.w/2)-25, farmingLabel.y+40, 50, 25};
}
