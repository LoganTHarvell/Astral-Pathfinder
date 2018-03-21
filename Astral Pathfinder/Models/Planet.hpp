//
//  Planet.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Planet_hpp
#define Planet_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include <string>

// MARK: Source Files
#include "GameObject.hpp"


// MARK: - Planet Parameters

namespace PlanetParameters {
  
  const std::string planetTextureFile = "Resources/Assets/planet.png";
  const int planetTexSize = 8;
  const int minFertility = 0;
  const int fertilityRange = (200-minFertility);
  const int minDeposits = 100;
  const int depositsRange = (600-minDeposits);
  const int startFarmingPercent = 50;
  const int startMiningPercent = 100 - startFarmingPercent;
  
  // Defines resource information
  const int startPopulation = 5000;
  const float foodRqmt = 0.02;
  const float farmingCost = 0.04;
  const int miningCost = 30;
  const int fuelCost = 250;
  const float infrastructureCost = 0.05;
}


// MARK: - Planet Class

class Planet: public GameObject {

public:
  // MARK: - Initialization Methods
  void initHomeworld();
  void initPlanet();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gs);
  void render(Game::State *gs);
  
  // Planet States
  enum Status {
    undiscovered,
    discovered,
    colonized
  };
  
  // MARK: - Planet Methods
  Status getStatus() { return status; };
  
  SDL_Point getCoordinates() { return coordinates; };
  
  int getDeposits() { return deposits; };
  int getFertility() { return fertility; };
  SDL_Point getLocation() { return coordinates; };
  int getPopulation() { return population; };
  int getFood() { return food; };
  int getMinerals() { return minerals; };
  
  int getDepositsPercent() { return depositsPercent; };
  int getFertilityPercent() { return fertilityPercent; };
  int getInfraPercent() { return infraPercent; };
  int getReservePercent() { return reservePercent; };
  void setDepositsPercent(int percent) { depositsPercent = percent; };
  void setFertilityPercent(int percent) { fertilityPercent = percent; };
  void setInfraPercent(int percent) { infraPercent = percent; };
  void setReservePercent(int percent) { reservePercent = percent; };
  
  void clicked();
  void revertClick();
  
  bool playerIsDocked() { return playerDocked; };
  bool alienIsDocked() { return alienDocked; };
  void toggleDockedShip(int tag);
  
private:
  // MARK: - Planet Fields
  Status status;
  SDL_Point coordinates;

  // resources
  int population;
  int deposits, fertility;
  int depositsPercent, fertilityPercent, infraPercent, reservePercent;
  int minerals, food;
  
  bool playerDocked;
  bool alienDocked;
  
  // MARK: - Helper Methods
  void updateStatus();
  
  // TODO: - Implement methods
  void updatePopulation();
  void updateMining();
  void updateFarming();
  
  SDL_Point uiPosition(SDL_Point p);
};

#endif /* Planet_hpp */
