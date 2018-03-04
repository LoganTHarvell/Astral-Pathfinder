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
  depoSlider.init(slideBase, circle);
  fertSlider.init(slideBase2, circle2);
}


// MARK: - Game Loop Methods

void PlanetInfo::render() {
  depositsText.render();
  fertilityText.render();
  dpText.render();
  fpText.render();
  depoSlider.render();
  fertSlider.render();
}

void PlanetInfo::clean() {
  depositsText.clean();
  fertilityText.clean();
  dpText.clean();
  fpText.clean();
  depoSlider.clean();
  fertSlider.clean();
}


// MARK: - PlanetInfo Methods

void PlanetInfo::setText(Planet p) {
  setBoxes(p);
  depoSlider.setTextures(p.getDepositsPercent());
  fertSlider.setTextures(p.getFertilityPercent());
}

bool PlanetInfo::checkClick(Game::State *gameState) {
  int x = gameState->clickLocation.x;
  int y = gameState->clickLocation.y;
  SDL_Rect tempDepo = depoSlider.getCirclePosition();
  SDL_Rect tempFert = fertSlider.getCirclePosition();
  if((x > tempDepo.x) && (x < tempDepo.x + tempDepo.w)
     && (y > tempDepo.y) && (y < tempDepo.y + tempDepo.h)) {
    sliderNum = 1;
    return true;
  }
  
  if((x > tempFert.x) && (x < tempFert.x + tempFert.w)
     && (y > tempFert.y) && (y < tempFert.y + tempFert.h)) {
    sliderNum = 2;
    return true;
  }
  
  sliderNum = -1;
  return false;
}

int PlanetInfo::moveSlider(Game::State *gameState) {
  SDL_Rect temp;
  int p = 0;
  int x = gameState->dragLocation.x;
  
  if(sliderNum == 1)
    temp = depoSlider.getBasePosition();
  
  if(sliderNum == 2)
    temp = fertSlider.getBasePosition();
  
  if((x > temp.x) && (x < temp.x + temp.w + 1)) {
    if(sliderNum == 1)
      p = depoSlider.setCirclePosition(x);
    
    if(sliderNum == 2)
      p = fertSlider.setCirclePosition(x);
    setNewPercent(p);
    return p;
  }
  
  return -1;
}

// MARK: - Helper Methods

void PlanetInfo::setBoxes(Planet p) {
  std::string depo = "Deposits: " + std::to_string(p.getDeposits());
  std::string fert = "Fertility: " + std::to_string(p.getFertility());
  std::string depoPercent = " : " + setSpaces(p.getDepositsPercent()) + std::to_string(p.getDepositsPercent()) + "%";
  std::string fertPercent = " : " + setSpaces(p.getFertilityPercent()) + std::to_string(p.getFertilityPercent()) + "%";
  
  depositsText.setMessage(depo.c_str());
  fertilityText.setMessage(fert.c_str());
  dpText.setMessage(depoPercent.c_str());
  fpText.setMessage(fertPercent.c_str());
}

void PlanetInfo::setNewPercent(int p) {
  if(sliderNum == 1) {
    std::string depoPercent = " : " + setSpaces(p) + std::to_string(p) + "%";
    dpText.setMessage(depoPercent.c_str());
  }
  
  if(sliderNum == 2) {
    std::string fertPercent = " : " + setSpaces(p) + std::to_string(p) + "%";
    fpText.setMessage(fertPercent.c_str());
  }
}

std::string PlanetInfo::setSpaces(int p) {
  std::string s;
  
  if(p >= 0 && p < 10)
    s = s + " " + " ";
  else if(p >= 10 && p < 100)
    s = s + " ";
  
  return s;
}
