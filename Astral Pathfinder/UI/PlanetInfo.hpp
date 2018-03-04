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

// MARK: - PlanetInfo Parameters

namespace InfoParameters {
  const SDL_Rect depositsRect = {1245, 510, 200, 50};
  const SDL_Rect fertilityRect = {1245, 650, 200, 50};
  const SDL_Rect depositsPercentRect = {1450, 510, 75, 50};
  const SDL_Rect fertilityPercentRect = {1450, 650, 75, 50};
  const SDL_Rect slideBase = {1245, 582, 265, 35};
  const SDL_Rect circle = {1245, 570, 50, 50};
  const SDL_Rect slideBase2 = {1245, 722, 265, 35};
  const SDL_Rect circle2 = {1245, 710, 50, 50};
}

class PlanetInfo {
public:
  // MARK: - PlanetInfo Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void render();
  void clean();

  
  // MARK: - PlanetInfo Methods
  void setText(Planet p);
  bool checkClick(Game::State *gameState);
  int moveSlider(Game::State *gameState);
  int getSliderNum() { return sliderNum; }
  void setSliderNum(int n) { sliderNum = n; }

  
private:
  // MARK: - PlanetInfo Fields
  TextBox depositsText, fertilityText, dpText, fpText;
  Slider depoSlider, fertSlider;
  int sliderNum = -1;
  
  // MARK: - Helper Methods
  void setBoxes(Planet p);
  void setNewPercent(int p);
  std::string setSpaces(int p);

};

#endif /* PlanetInfo_hpp */
