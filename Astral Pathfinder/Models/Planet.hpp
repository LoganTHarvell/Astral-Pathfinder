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
  
  // Planet texture information
  const std::string planetTextureFile = "Resources/Assets/planet.png";
  const int planetTexSize = 16;
  
  // Planet initial attribute information
  const int minFertility = 20;
  const int fertilityRange = (200-minFertility);
  const int minDeposits = 200;
  const int depositsRange = (1000-minDeposits);
  const int startInfraPercent = 50;
  const int startReservePercent = 100 - startInfraPercent;
  const int startMiningPercent = 100;
  const int startFarmingPercent = 100 - startMiningPercent;
  
  // Homeworld initial attribute values
  const int homeStartPopulation = 5000;
  const int homeStartFertility = 100;
  const int homeStartDeposits = 250;
  const int homeStartMiningPercent = 50;
  const int homeStartFarmingPercent = 100 - homeStartMiningPercent;
  const int homeStartInfraPercent = 0;
  const int homeStartReservePercent = 100 - homeStartInfraPercent;
  
  // Defines population growth information
  const int growthPeriod = 900;      // Frames per growth period
  const float starveRate = 0.0008;    // Starvation deaths per frame
  const float minBirthMultiplier = 0.1;
  const float birthMultiplierRange = (0.4-minBirthMultiplier);
  const float minDeathMultiplier = 0.05;
  const float deathMultiplierRange = (0.15-minDeathMultiplier);
 
  // Defines resource information
  const float foodRqmt = 0.02;      // Food required per person
  const float miningRate = 0.0001; // Minerals produced per person per frame
  const float farmingRate = 0.04;   // Food produced per person per frame
  const float fertDecay = 0.0001;
  const int fertDecayDelay = 10;
  const float infrastructureCost = 20;    // Infrastructure per mineral
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
  int getMinerals() { return minerals; };
  int getInfrastructure() { return infrastructure; };
  int getFood() { return food; };
  
  int getMiningPercent() { return miningPercent; };
  int getFarmingPercent() { return farmingPercent; };
  int getInfraPercent() { return infraPercent; };
  int getReservePercent() { return reservePercent; };
  void setMiningPercent(int percent) { miningPercent = percent; };
  void setFarmingPercent(int percent) { farmingPercent = percent; };
  void setInfraPercent(int percent) { infraPercent = percent; };
  void setReservePercent(int percent) { reservePercent = percent; };

  void clicked();
  void revertClick();
  
  bool playerIsDocked() { return playerDocked; };
  bool alienIsDocked() { return alienDocked; };
  void toggleDockedShip(int tag);
  int makeFuel(int amount);
  
private:
  // MARK: - Planet Fields
  Status status;
  SDL_Point coordinates;

  // Resources
  float population;
  float deposits, fertility;
  int miningPercent, farmingPercent, infraPercent, reservePercent;
  float minerals, infrastructure, food;
  
  // Population growth period attributes
  float birthMult, deathMult;   // Births/Deaths per person in a period
  int births, deaths;           // Total Birth/Deaths in a period
  float growthRate;             // Population change per frame
  
  // Food production flags
  bool isOverproducing;
  bool markedOverProd;
  Uint32 overproductionStartTime;
  
  // Docking flags
  bool playerDocked;
  bool alienDocked;
  
  // MARK: - Helper Methods
  void updateStatus();
  void updatePopulation(Uint32 frame);
  void updateMining();
  void updateFarming();
  
  SDL_Point uiPosition(SDL_Point p);
};

#endif /* Planet_hpp */
