//
//  PlanetManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef PlanetManager_hpp
#define PlanetManager_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "GameObject.hpp"
#include "Planet.hpp"
#include "ShipManager.hpp"


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
  void update(ShipManager *shipManager);
  void render();
  
  // MARK: - PlanetManager Methods
  Planet getPlanet(int n);
  void checkClicked(SDL_Event e);
  
private:
  // MARK: - Helper Methods
  // Initialiation helper methods
  static Planet initHomeworld();
  static Planet initPlanet();
  
  void collision(SDL_Rect r);
  
  // MARK: - PlanetManager Fields
  Planet planets[PlanetManagerParameters::numberOfPlanets];
  
};

#endif /* PlanetManager_hpp */
