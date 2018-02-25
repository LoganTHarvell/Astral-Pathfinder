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
  // MARK: - UIManager Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  
  // MARK: - UIManager Methods
  void setSelectedPlanet(Planet p);
  void resetSelectedPlanet();
  
private:
  // MARK: - UIManager Fields
  PlanetInfo planetInfo;
};

#endif /* UIManager_hpp */
