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
  void render();
  void clean();

  
  // MARK: - PlanetInfo Methods
  void setUiTextures(Planet p);
  bool checkClick(Game::State *gameState);
  bool moveSlider(Game::State *gameState);
  int getSliderPercent() { return slider.getPercent(); }

  
private:
  // MARK: - PlanetInfo Fields
  TextBox depositsText, fertilityText, dpText, fpText, mining, farming;
  Slider slider;
  SDL_Rect origin;
  SDL_Rect depositsRect;
  SDL_Rect fertilityRect;
  SDL_Rect miningLabel;
  SDL_Rect farmingLabel;
  SDL_Rect depositsPercentRect;
  SDL_Rect fertilityPercentRect;
  SDL_Rect slideBase;
  SDL_Rect circle;
  
  // MARK: - Helper Methods
  void setBoxes(Planet p);
  void setNewPercentText();
  std::string setStringSpaces(int p);
  void setUiRects();

};

#endif /* PlanetInfo_hpp */
