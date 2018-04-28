//
//  PlanetInfo.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/25/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef PlanetInfo_hpp
#define PlanetInfo_hpp

// MARK: Source Files
#include "Slider.hpp"
#include "TextBox.hpp"
#include "PlanetManager.hpp"
#include "Planet.hpp"

class PlanetInfo {
public:
  // MARK: - PlanetInfo Initialization
  void init(SDL_Rect src);
  
  // MARK: - Game Loop Methods
  void render(Game::State *gs, int population, bool playerDocked);
  void clean();

  
  // MARK: - PlanetInfo Methods
  void setUiTextures(Planet p);
  int checkClick(SDL_Point click);
  bool moveSlider(Game::State *gameState);
  int getSliderPercent();

  
private:
  // MARK: - PlanetInfo Fields
  TextBox dpText, fpText, miningLabel, farmingLabel,
          infraText, reserveText, ipText, rpText, locationText,
          popText, miningText, farmingText;
  Slider resourceSlider, depositSlider;
  SDL_Rect origin, miningLabelRect, farmingLabelRect,
           depositsPercentRect, fertilityPercentRect, slideBaseOne, circleOne,
           slideBaseTwo, circleTwo, infraRect, reserveRect, ipRect, rpRect,
           locationRect, popRect, miningRect, farmingRect;
  enum {
    neither, fertilitySlider, reserveSlider
  } slider = neither;
  
  // MARK: - Helper Methods
  void setBoxes(Planet p);
  void setNewPercentText();
  std::string setStringSpaces(int p);
  void setUiRects();

};

#endif /* PlanetInfo_hpp */
