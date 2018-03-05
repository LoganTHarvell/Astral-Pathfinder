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
  const SDL_Rect depositsRect = {1220, 510, 135, 35};
  const SDL_Rect fertilityRect = {1395, 510, 135, 35};
  const SDL_Rect miningLabel = {1220, 560, 75, 30};
  const SDL_Rect farmingLabel = {1455, 560, 75, 30};
  const SDL_Rect depositsPercentRect = {1232, 600, 50, 25};
  const SDL_Rect fertilityPercentRect = {1467, 600, 50, 25};
  const SDL_Rect slideBase = {1310, 582, 125, 15};
  const SDL_Rect circle = {NULL, 576, 25, 25};
}

class PlanetInfo {
public:
  // MARK: - PlanetInfo Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void render();
  void clean();

  
  // MARK: - PlanetInfo Methods
  void setUiTextures(Planet p);
  bool checkClick(Game::State *gameState);
  int moveSlider(Game::State *gameState);

  
private:
  // MARK: - PlanetInfo Fields
  TextBox depositsText, fertilityText, dpText, fpText, mining, farming;
  Slider slider;
  
  // MARK: - Helper Methods
  void setBoxes(Planet p);
  void setNewPercent(int p);
  std::string setStringSpaces(int p);

};

#endif /* PlanetInfo_hpp */
