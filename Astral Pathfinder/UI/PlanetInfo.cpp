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

  dpText.init(depositsPercentRect);
  fpText.init(fertilityPercentRect);
  mining.init(miningLabel);
  farming.init(farmingLabel);
  sliderOne.init(slideBaseOne, circleOne);
  infrastructureText.init(infraRect);
  reserveText.init(reserveRect);
  ipText.init(ipRect);
  rpText.init(rpRect);
  sliderTwo.init(slideBaseTwo, circleTwo);
  locationText.init(locationRect);
  popText.init(popRect);
  miningText.init(miningRect);
  farmingText.init(farmingRect);
}


// MARK: - Game Loop Methods

void PlanetInfo::render() {
  dpText.render();
  fpText.render();
  mining.render();
  farming.render();
  sliderOne.render();
  infrastructureText.render();
  reserveText.render();
  ipText.render();
  rpText.render();
  sliderTwo.render();
  locationText.render();
  popText.render();
  miningText.render();
  farmingText.render();
}

void PlanetInfo::clean() {
  dpText.clean();
  fpText.clean();
  mining.clean();
  farming.clean();
  sliderOne.clean();
  infrastructureText.clean();
  reserveText.clean();
  ipText.clean();
  rpText.clean();
  sliderTwo.clean();
  locationText.clean();
  popText.clean();
  miningText.clean();
  farmingText.clean();
}


// MARK: - PlanetInfo Methods

void PlanetInfo::setUiTextures(Planet p) {
  setBoxes(p);
  
  if (sliderOne.isInitialized() && sliderTwo.isInitialized()) {
    SDL_Rect tmpR;
    float ratio;
    // Sets correct slider position for given planet
    ratio = p.getFertilityPercent()/100.0f;
    tmpR = sliderOne.getBaseRect();
    sliderOne.setSliderPosition(static_cast<int>(tmpR.w * ratio));
    
    ratio = p.getReservePercent()/100.0f;
    tmpR = sliderTwo.getBaseRect();
    sliderTwo.setSliderPosition(static_cast<int>(tmpR.w * ratio));
  }
  // Sets slider textures if not initialized
  else {
    sliderOne.setTextures(p.getFertilityPercent());
    sliderTwo.setTextures(p.getReservePercent());
  }
  
}

int PlanetInfo::checkClick(Game::State *gameState) {
  int x = gameState->clickLocation.x;
  int y = gameState->clickLocation.y;
  SDL_Rect temp;
  
  temp = sliderOne.getSliderRect();
  if((x > temp.x) && (x < temp.x + temp.w)
     && (y > temp.y) && (y < temp.y + temp.h)) {
    sliderNum = 1;
    return 1;
  }
  
  temp = sliderTwo.getSliderRect();
  if((x > temp.x) && (x < temp.x + temp.w)
     && (y > temp.y) && (y < temp.y + temp.h)) {
    sliderNum = 2;
    return 2;
  }
  
  sliderNum = -1;
  return -1;
}

bool PlanetInfo::moveSlider(Game::State *gameState) {
  SDL_Rect temp;
  
  if(sliderNum == 1)
    temp = sliderOne.getBaseRect();
  
  else
    temp = sliderTwo.getBaseRect();
  
  int x = gameState->dragLocation.x - temp.x;
  
  if(sliderNum == 1 && (x > 0) && (x < temp.w + 1)) {
    sliderOne.setSliderPosition(x);
    setNewPercentText();
    return true;
  }
  
  if(sliderNum == 2 && (x > 0) && (x < temp.w + 1)) {
    sliderTwo.setSliderPosition(x);
    setNewPercentText();
    return true;
  }
  
  return false;
}

int PlanetInfo::getSliderPercent() {
  if(sliderNum == 1)
    return sliderOne.getPercent();
  
  if(sliderNum == 2)
    return sliderTwo.getPercent();
  
  return NULL;
}

// MARK: - Helper Methods

void PlanetInfo::setBoxes(Planet p) {
  std::string depo = std::to_string(p.getDeposits());
  std::string location = "Location: " + setStringSpaces(p.getLocation().x) + std::to_string(p.getLocation().x)
                                      + "," + std::to_string(p.getLocation().y);
  std::string population = "Population: " + setStringSpaces(p.getPopulation()) + std::to_string(p.getPopulation());
  std::string food = "Farming: " + setStringSpaces(p.getFood()) + std::to_string(p.getFood()) + "/"
                      + std::to_string(p.getFertility());
  std::string minerals = "Mining: " + setStringSpaces(p.getMinerals()) + std::to_string(p.getMinerals()) + "/"
                          + std::to_string(p.getDeposits());
  std::string depoPercent = setStringSpaces(p.getDepositsPercent()) + std::to_string(p.getDepositsPercent()) + "%";
  std::string fertPercent = setStringSpaces(p.getFertilityPercent()) + std::to_string(p.getFertilityPercent()) + "%";
  std::string infPercent = setStringSpaces(p.getInfraPercent()) + std::to_string(p.getInfraPercent()) + "%";
  std::string resPercent = setStringSpaces(p.getReservePercent()) + std::to_string(p.getReservePercent()) + "%";
  
  locationText.setMessage(location.c_str());
  popText.setMessage(population.c_str());
  miningText.setMessage(minerals.c_str());
  farmingText.setMessage(food.c_str());
  dpText.setMessage(depoPercent.c_str());
  fpText.setMessage(fertPercent.c_str());
  ipText.setMessage(infPercent.c_str());
  rpText.setMessage(resPercent.c_str());
  mining.setMessage("Mining");
  farming.setMessage("Farming");
  infrastructureText.setMessage("Infrastructure");
  reserveText.setMessage("Reserve");
}

void PlanetInfo::setNewPercentText() {
  int p = getSliderPercent();
  
  if(sliderNum == 1) {
    std::string depoPercent = setStringSpaces(100-p) + std::to_string(100-p) + "%";
    dpText.setMessage(depoPercent.c_str());
    
    std::string fertPercent = setStringSpaces(p) + std::to_string(p) + "%";
    fpText.setMessage(fertPercent.c_str());
  }
  
  if(sliderNum == 2) {
    std::string infPercent = setStringSpaces(100-p) + std::to_string(100-p) + "%";
    ipText.setMessage(infPercent.c_str());
    
    std::string resPercent = setStringSpaces(p) + std::to_string(p) + "%";
    rpText.setMessage(resPercent.c_str());
  }
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
  
  locationRect = {leftBuffer, topBuffer, 135, 35};
  popRect = {midW+10, topBuffer, 135, 35};
  miningRect = {leftBuffer, locationRect.y+50, 135, 35};
  farmingRect = {midW+10, popRect.y+50, 135, 35};
  miningLabel = {leftBuffer, miningRect.y+50, 75, 30};
  depositsPercentRect = {miningLabel.x+(miningLabel.w/2)-25, miningLabel.y+40, 50, 25};
  slideBaseOne = {leftBuffer+miningLabel.w+15, miningLabel.y+20, 125, 15};
  circleOne = {NULL, slideBaseOne.y-6, 25, 25};
  farmingLabel = {slideBaseOne.x+slideBaseOne.w+15, miningLabel.y, 75, 30};
  fertilityPercentRect = {farmingLabel.x+(farmingLabel.w/2)-25, farmingLabel.y+40, 50, 25};
  infraRect = {leftBuffer, depositsPercentRect.y+50, 75, 30};
  ipRect = {infraRect.x+(infraRect.w/2)-25, infraRect.y+40, 50, 25};
  slideBaseTwo = {leftBuffer+infraRect.w+15, infraRect.y+20, 125, 15};
  reserveRect = {slideBaseTwo.x+slideBaseTwo.w+15, infraRect.y, 75, 30};
  rpRect = {reserveRect.x+(reserveRect.w/2)-25, reserveRect.y+40, 50, 25};
  circleTwo = {NULL, slideBaseTwo.y-6, 25, 25};
}
