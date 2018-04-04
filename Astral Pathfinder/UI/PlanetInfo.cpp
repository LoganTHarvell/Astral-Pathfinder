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
  miningLabel.init(miningLabelRect);
  farmingLabel.init(farmingLabelRect);
  sliderOne.init(slideBaseOne, circleOne);
  infraText.init(infraRect);
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

void PlanetInfo::render(Game::State *gs, int population) {
  locationText.render(gs);
  popText.render(gs);
  miningText.render(gs);
  farmingText.render(gs);
  
  if(population > 0) {
    dpText.render(gs);
    fpText.render(gs);
    miningLabel.render(gs);
    farmingLabel.render(gs);
    sliderOne.render();
    infraText.render(gs);
    reserveText.render(gs);
    ipText.render(gs);
    rpText.render(gs);
    sliderTwo.render();
  }
}

void PlanetInfo::clean() {
  dpText.clean();
  fpText.clean();
  miningLabel.clean();
  farmingLabel.clean();
  sliderOne.clean();
  infraText.clean();
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
  using namespace SliderParameters;
  
  setBoxes(p);
  
  if (!sliderOne.isInitialized() && !sliderTwo.isInitialized()
      && (p.getPopulation() > 0)) {
    sliderOne.setTextures(p.getFarmingPercent());
    sliderOne.colorMod(baseColor, sliderColor);
    sliderTwo.setTextures(p.getReservePercent());
    sliderTwo.colorMod(baseColor, sliderColor);
  }
  else {
    sliderOne.updateSliderPosition(p.getFarmingPercent());
    sliderTwo.updateSliderPosition(p.getReservePercent());
  }
}

int PlanetInfo::checkClick(SDL_Point click) {
  SDL_Rect temp;
  
  temp = sliderOne.getSliderRect();
  if((click.x > temp.x) && (click.x < temp.x + temp.w)
     && (click.y > temp.y) && (click.y < temp.y + temp.h)) {
    slider = fertilitySlider;
    return fertilitySlider;
  }
  
  temp = sliderTwo.getSliderRect();
  if((click.x > temp.x) && (click.x < temp.x + temp.w)
     && (click.y > temp.y) && (click.y < temp.y + temp.h)) {
    slider = reserveSlider;
    return reserveSlider;
  }
  
  slider = neither;
  return neither;
}

bool PlanetInfo::moveSlider(Game::State *gameState) {
  SDL_Rect temp;
  
  if(slider == fertilitySlider)
    temp = sliderOne.getBaseRect();
  
  else
    temp = sliderTwo.getBaseRect();
  
  int x = gameState->dragLocation.x - temp.x;
  
  if(slider == fertilitySlider && (x > 0) && (x < temp.w + 2)) {
    sliderOne.setSliderPosition(x);
    setNewPercentText();
    return true;
  }
  
  if(slider == reserveSlider && (x > 0) && (x < temp.w + 2)) {
    sliderTwo.setSliderPosition(x);
    setNewPercentText();
    return true;
  }
  
  return false;
}

int PlanetInfo::getSliderPercent() {
  if(slider == fertilitySlider)
    return sliderOne.getPercent();
  
  if(slider == reserveSlider)
    return sliderTwo.getPercent();
  
  return NULL;
}

// MARK: - Helper Methods

// TODO: - Clean up all below code, add comments, whitespace
// split long lines into multiple like this, assign long stuff to temp variables

void PlanetInfo::setBoxes(Planet p) {
  SDL_Point mapLocation = p.getCenter();
  std::string location, population, food, minerals,
              depoPercent, fertPercent, infPercent, resPercent;
  int populationAmount = p.getPopulation();
  
  location = "Location: " + setStringSpaces(mapLocation.x) + std::to_string(mapLocation.x)
  + "," + std::to_string(mapLocation.y);
  
  if(populationAmount == 0) {
    if (p.getStatus() == Planet::undiscovered) population = "Undiscovered";
    else if (p.getStatus() == Planet::discovered) population = "Discovered";
    
    food = "Fertility: " + std::to_string(p.getFertility());
    minerals = "Deposits: " + std::to_string(p.getDeposits());
    popText.setRect(origin.x+(origin.w/2)+40, (origin.w/2)-50);
    farmingText.setRect(origin.x+(origin.w/2)+40, (origin.w/2)-50);
    miningText.setRect(origin.x+5, (origin.w/2)-40);
    locationText.setRect(origin.x+5, (origin.w/2)-40);
  }
  
  if (populationAmount > 0) {
    population = "Population: " + setStringSpaces(p.getPopulation())
                  + std::to_string(p.getPopulation()) + "/"
                  + std::to_string(p.getInfrastructure());
    food = "Farming: " + setStringSpaces(p.getFood()) + std::to_string(p.getFood()) + "/"
                        + std::to_string(p.getFertility());
    minerals = "Mining: " + setStringSpaces(p.getMinerals()) + std::to_string(p.getMinerals()) + "/"
                            + std::to_string(p.getDeposits());
    depoPercent = setStringSpaces(p.getMiningPercent()) + std::to_string(p.getMiningPercent()) + "%";
    fertPercent = setStringSpaces(p.getFarmingPercent()) + std::to_string(p.getFarmingPercent()) + "%";
    infPercent = setStringSpaces(p.getInfraPercent()) + std::to_string(p.getInfraPercent()) + "%";
    resPercent = setStringSpaces(p.getReservePercent()) + std::to_string(p.getReservePercent()) + "%";
    popText.setRect(origin.x+(origin.w/2), (origin.w/2)-10);
    farmingText.setRect(origin.x+(origin.w/2), (origin.w/2)-10);
    miningText.setRect(origin.x+5, (origin.w/2)-15);
    locationText.setRect(origin.x+5, (origin.w/2)-15);
    
    dpText.setMessage(depoPercent.c_str());
    fpText.setMessage(fertPercent.c_str());
    ipText.setMessage(infPercent.c_str());
    rpText.setMessage(resPercent.c_str());
    
    if(miningLabel.checkNull()) {
      miningLabel.setMessage("Mining");
      farmingLabel.setMessage("Farming");
      infraText.setMessage("Infrastructure");
      reserveText.setMessage("Reserve");
    }
  }
  
  popText.setMessage(population.c_str());
  miningText.setMessage(minerals.c_str());
  farmingText.setMessage(food.c_str());
  locationText.setMessage(location.c_str());
  
}

void PlanetInfo::setNewPercentText() {
  int p = getSliderPercent();
  
  if(slider == fertilitySlider) {
    std::string depoPercent = setStringSpaces(100-p) + std::to_string(100-p) + "%";
    dpText.setMessage(depoPercent.c_str());
    
    std::string fertPercent = setStringSpaces(p) + std::to_string(p) + "%";
    fpText.setMessage(fertPercent.c_str());
  }
  
  if(slider == reserveSlider) {
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
  int buffer = 5; // Small buffer from borders or other elements
  int midW = origin.x+(origin.w/2); // Midpoint of width
  int gapH = origin.h/30; // Spaces between elements
  int sliderW = static_cast<int>(origin.w/2.66);
  
  SDL_Point header = {(origin.w/2)-(buffer*3), origin.h/10};
  SDL_Point label = {static_cast<int>(origin.w/4.57), origin.h/10};
  SDL_Point percent = {static_cast<int>(origin.w/6.4), origin.h/12};
  
  locationRect = {origin.x+buffer, origin.y+(buffer*4),
                  header.x, header.y};
  popRect = {midW+(buffer*2), locationRect.y, header.x, header.y};
  miningRect = {locationRect.x, locationRect.y+locationRect.h+gapH,
                header.x, header.y};
  farmingRect = {popRect.x, miningRect.y, header.x, header.y};
  miningLabelRect = {locationRect.x, miningRect.y+miningRect.h+(gapH*2),
                     label.x, label.y};
  depositsPercentRect = {miningLabelRect.x+(miningLabelRect.w/2)-(buffer*5),
                        miningLabelRect.y+miningLabelRect.h+gapH, percent.x, percent.y};
  slideBaseOne = {midW-(sliderW/2), depositsPercentRect.y,
                  sliderW, origin.h/20};
  circleOne = {NULL, slideBaseOne.h/2-((buffer*5)/2)+slideBaseOne.y,
               slideBaseOne.w/5, slideBaseOne.w/5};
  farmingLabelRect = {slideBaseOne.x+slideBaseOne.w+(buffer*3),
                      miningLabelRect.y, label.x, label.y};
  fertilityPercentRect = {farmingLabelRect.x+(farmingLabelRect.w/2)-(buffer*5),
                          depositsPercentRect.y, percent.x, percent.y};
  infraRect = {locationRect.x, depositsPercentRect.y+depositsPercentRect.h+(gapH*2),
              buffer*20, label.y};
  ipRect = {depositsPercentRect.x, infraRect.y+infraRect.h+gapH,
            percent.x, percent.y};
  slideBaseTwo = {slideBaseOne.x, ipRect.y,
                  slideBaseOne.w, slideBaseOne.h};
  circleTwo = {NULL, slideBaseTwo.h/2-((buffer*5)/2)+slideBaseTwo.y,
               circleOne.w, circleOne.h};
  reserveRect = {farmingLabelRect.x, infraRect.y, label.x, label.y};
  rpRect = {fertilityPercentRect.x, ipRect.y, percent.x, percent.y};
}
