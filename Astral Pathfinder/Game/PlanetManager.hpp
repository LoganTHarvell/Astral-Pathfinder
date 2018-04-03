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
#include "Game.hpp"
#include "Planet.hpp"


// MARK: - PlanetManager Parameters

namespace PlanetManagerParameters {
  
  const int numberOfPlanets = 25;
  
}


// MARK: - PlanetManager Class

class PlanetManager {
  
public:
  // MARK: - Galaxy Initialization
  void initGalaxy();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, ShipManager *shipManager);
  void render(Game::State *gameState);
  
  // MARK: - PlanetManager Methods
  Planet getPlanet(int n);
  Planet getSelectedPlanet();
  bool planetIsDocked();
  Planet getDockedPlanet();
  void setPlanetMiningPercent(int p, int flag);
  void setPlanetFarmingPercent(int p, int flag);
  void setPlanetInfraPercent(int p, int flag);
  void setPlanetReservePercent(int p, int flag);
  
  int fuelDockedShip();
  int getTotalPopulation() { return totalPopulation; }
  
private:
  // MARK: - Helper Methods
  // Initialiation helper methods
  static Planet initHomeworld();
  static Planet initPlanet();
  
  void handleClickEvent(SDL_Point p, Game::State *gs);
  void selectPlanet(bool *planetSelected);
  void deselectPlanet(bool *planetSelected);
  
  void handleCollisions(ShipManager *sm);
  
  // MARK: - PlanetManager Fields
  std::vector<Planet> planets;
  
  int dockedPlanetIndex;
  int selectedPlanetIndex;
  int discoveryCount;
  int totalPopulation;

};

#endif /* PlanetManager_hpp */
