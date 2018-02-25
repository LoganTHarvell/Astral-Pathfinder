//
//  PlanetInfo.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/25/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef PlanetInfo_hpp
#define PlanetInfo_hpp

#include "TextBox.hpp"
#include "Planet.hpp"

class PlanetInfo {
public:
  void init();
  
  void update();
  void render();
  
  void setBoxes(Planet p);
  void resetText();

private:
  TextBox depositsText, fertilityText;
};

#endif /* PlanetInfo_hpp */
