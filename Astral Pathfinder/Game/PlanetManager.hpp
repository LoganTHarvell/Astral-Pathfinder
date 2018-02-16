//
//  Galaxy.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Galaxy_hpp
#define Galaxy_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "GameObject.hpp"
#include "Planet.hpp"


// MARK: - PlanetManager Parameters

namespace PlanetManagerParameters {
  
  const int numberOfPlanets = 50;
  
}


// MARK: - PlanetManager Class

class PlanetManager {
  
public:
  // MARK: - Galaxy Initialization
  void initGalaxy();
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  
  // MARK: - PlanetManager Methods
  Planet getPlanet(int n);
  
private:
  // MARK: - Initialization Helper Methods
  static Planet initHomeworld();
  static Planet initPlanet();
  
  // MARK: - PlanetManager Fields
  Planet planets[PlanetManagerParameters::numberOfPlanets];
  
};

#endif /* Galaxy_hpp */
