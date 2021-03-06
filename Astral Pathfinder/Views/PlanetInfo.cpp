//
//  PlanetInfo.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/25/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Sub-screen manager for displaying relevant and updated planet information.
//  Contains all necessary UI elements and handles their initialization, events,
//  update, and rendering.

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
  resourceSlider.init(slideBaseOne, circleOne);
  infraText.init(infraRect);
  reserveText.init(reserveRect);
  ipText.init(ipRect);
  rpText.init(rpRect);
  depositSlider.init(slideBaseTwo, circleTwo);
  locationText.init(locationRect);
  popText.init(popRect);
  miningText.init(miningRect);
  farmingText.init(farmingRect);
}


// MARK: - Game Loop Methods

void PlanetInfo::render(Game::State *gs, int population,
                        bool playerDocked) {
  locationText.render(gs);
  popText.render(gs);
  miningText.render(gs);
  farmingText.render(gs);
  
  if (population > 0 || playerDocked) {
    dpText.render(gs);
    fpText.render(gs);
    miningLabel.render(gs);
    farmingLabel.render(gs);
    resourceSlider.render(Game::renderer);
    infraText.render(gs);
    reserveText.render(gs);
    ipText.render(gs);
    rpText.render(gs);
    depositSlider.render(Game::renderer);
  }
}

void PlanetInfo::clean() {
  dpText.clean();
  fpText.clean();
  miningLabel.clean();
  farmingLabel.clean();
  resourceSlider.clean();
  infraText.clean();
  reserveText.clean();
  ipText.clean();
  rpText.clean();
  depositSlider.clean();
  locationText.clean();
  popText.clean();
  miningText.clean();
  farmingText.clean();
}


// MARK: - PlanetInfo Methods

void PlanetInfo::setUiTextures(Planet p) {
  using namespace Parameters::UI::Slider;
  
  setBoxes(p);
  
  if (!resourceSlider.isInitialized() && !depositSlider.isInitialized()
      && (p.getPopulation() > 0 || p.playerIsDocked())) {
    resourceSlider.setTextures(baseTexFile, sliderTexFile,
                               Game::renderer, p.getFarmingPercent());
    resourceSlider.colorMod(baseColor, sliderColor);
    depositSlider.setTextures(baseTexFile, sliderTexFile,
                              Game::renderer, p.getReservePercent());
    depositSlider.colorMod(baseColor, sliderColor);
  }
  else {
    resourceSlider.updateSliderPosition(p.getFarmingPercent());
    depositSlider.updateSliderPosition(p.getReservePercent());
  }
}

// Checks if a click is on a slider
int PlanetInfo::checkClick(SDL_Point click) {
  SDL_Rect temp;
  
  temp = resourceSlider.getBaseRect();
  temp.y = resourceSlider.getSliderRect().y;
  temp.h = resourceSlider.getSliderRect().h;
  if ((click.x > temp.x) && (click.x < temp.x + temp.w)
     && (click.y > temp.y) && (click.y < temp.y + temp.h)) {
    slider = fertilitySlider;
    return fertilitySlider;
  }
  
  temp = depositSlider.getBaseRect();
  temp.y = depositSlider.getSliderRect().y;
  temp.h = depositSlider.getSliderRect().h;
  if ((click.x > temp.x) && (click.x < temp.x + temp.w)
     && (click.y > temp.y) && (click.y < temp.y + temp.h)) {
    slider = reserveSlider;
    return reserveSlider;
  }
  
  slider = neither;
  return neither;
}

// Moves the slider if in bounds and mouse is clicked/dragged on a slider
bool PlanetInfo::moveSlider(Game::State *gameState) {
  SDL_Rect temp;
  
  if (slider == fertilitySlider)
    temp = resourceSlider.getBaseRect();
  
  else
    temp = depositSlider.getBaseRect();
  
  int x = gameState->dragLocation.x - temp.x;
  
  if (slider == fertilitySlider && (x > 0) && (x < temp.w + 2)) {
    resourceSlider.setSliderPosition(x);
    setNewPercentText();
    return true;
  }
  
  if (slider == reserveSlider && (x > 0) && (x < temp.w + 2)) {
    depositSlider.setSliderPosition(x);
    setNewPercentText();
    return true;
  }
  
  return false;
}

int PlanetInfo::getSliderPercent() {
  if (slider == fertilitySlider)
    return resourceSlider.getPercent();
  
  if (slider == reserveSlider)
    return depositSlider.getPercent();
  
  return NULL;
}


// MARK: - Helper Methods

// TODO: Clean up all below code, add comments, whitespace, hard coded values
// split long lines into multiple like this, use temp variables for readability

// Sets text to each textbox in PlanetInfo
void PlanetInfo::setBoxes(Planet p) {
  SDL_Point mapLocation = p.mapPosition();
  std::string location, population, food, minerals,
              depoPercent, fertPercent, infPercent, resPercent;
  int populationAmount = p.getPopulation();
  
  location = "Location: " + setStringSpaces(mapLocation.x) + std::to_string(mapLocation.x)
  + "," + std::to_string(mapLocation.y);
  
  if (populationAmount == 0 && !p.playerIsDocked()) {
    if (p.getStatus() == Planet::undiscovered) population = "Undiscovered";
    else if (p.getStatus() == Planet::discovered) population = "Discovered";
    
    food = "Fertility: " + std::to_string(p.getFertility());
    minerals = "Deposits: " + std::to_string(p.getDeposits());
    popText.setRectXW(origin.x+(origin.w/2)+40, (origin.w/2)-50);
    farmingText.setRectXW(origin.x+(origin.w/2)+40, (origin.w/2)-50);
    miningText.setRectXW(origin.x+5, (origin.w/2)-40);
    locationText.setRectXW(origin.x+5, (origin.w/2)-40);
  }
  
  if (populationAmount > 0 || p.playerIsDocked()) {
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
    popText.setRectXW(origin.x+(origin.w/2), (origin.w/2)-10);
    farmingText.setRectXW(origin.x+(origin.w/2), (origin.w/2)-10);
    miningText.setRectXW(origin.x+5, (origin.w/2)-15);
    locationText.setRectXW(origin.x+5, (origin.w/2)-15);
    
    dpText.setMessage(depoPercent.c_str());
    fpText.setMessage(fertPercent.c_str());
    ipText.setMessage(infPercent.c_str());
    rpText.setMessage(resPercent.c_str());
    
    if (miningLabel.checkNull()) {
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

// Updates the percent values for each slider amount
void PlanetInfo::setNewPercentText() {
  int p = getSliderPercent();
  
  if (slider == fertilitySlider) {
    std::string depoPercent = setStringSpaces(100-p) + std::to_string(100-p) + "%";
    dpText.setMessage(depoPercent.c_str());
    
    std::string fertPercent = setStringSpaces(p) + std::to_string(p) + "%";
    fpText.setMessage(fertPercent.c_str());
  }
  
  if (slider == reserveSlider) {
    std::string infPercent = setStringSpaces(100-p) + std::to_string(100-p) + "%";
    ipText.setMessage(infPercent.c_str());
    
    std::string resPercent = setStringSpaces(p) + std::to_string(p) + "%";
    rpText.setMessage(resPercent.c_str());
  }
}

// Creates buffer with spaces for displayed numbers on UI so textboxes don't adjust
std::string PlanetInfo::setStringSpaces(int p) {
  std::string s;
  
  if (p >= 0 && p < 10)
    s = s + " " + " ";
  else if (p >= 10 && p < 100)
    s = s + " ";
  
  return s;
}

// TODO: Clean this up, hard coded values must be moved to parameters
// Sets rects for each item in the PlanetInfo boxes
void PlanetInfo::setUiRects() {
  int buffer = 5;                   // Buffer from borders or other elements
  int midW = origin.x+(origin.w/2); // Midpoint of width
  int gapH = origin.h/30;           // Spaces between elements
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
