//
//  UIManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef UIManager_hpp
#define UIManager_hpp

// MARK: Source Files
#include "PlanetInfo.hpp"
#include "Planet.hpp"

class UIManager {
  
public:
  void init();
  
  void update();
  void render();
  void setText(Planet p);
  void resetText();
  
private:
  PlanetInfo planetInfo;
};

#endif /* UIManager_hpp */
