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
#include "EventsComponent.hpp"


// MARK: - Planet Parameters

namespace PlanetParameters {
  
  // Planet texture information
  const std::string planetTextureFile = "../Resources/planet.png";
  const int planetTexSize = 16;
  
  const std::string planetOutlineFile = "../Resources/planetOutline.png";
  const int planetOutlineSize = 24;
  
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
  const int homeStartMiningPercent = 58;
  const int homeStartFarmingPercent = 100 - homeStartMiningPercent;
  const int homeStartInfraPercent = 0;
  const int homeStartReservePercent = 100 - homeStartInfraPercent;
  
  // Defines population growth information
  const int growthPeriod = 1200;      // Frames per growth period
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

  // Random event chances
  const float plagueRate = 0.05;
  const float blightRate = 0.1;
  const float mineCollapseRate = 0.3;
  
  // Random event multipliers
  const float plagueMultiplier = (deathMultiplierRange+minDeathMultiplier)*1.33;
  const float blightMultiplier = 0.75;
  const float mineCollapseMultiplier = 0.5;
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
  EventsComponent getEvents() { return *eventManager; }
  
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
  void toggleDockedShip(int tag, Uint32 frame);
  int makeFuel(int amount);
  SDL_Point mapPosition();
  
private:
  // MARK: - Planet Fields
  
  Status status;
  SDL_Point coordinates;
  EventsComponent *eventManager = nullptr;
  SDL_Texture *outlineTexture;
  SDL_Rect outlineRect;

  // Resources
  float population, populationCheck;
  float deposits, fertility;
  int miningPercent, farmingPercent, infraPercent, reservePercent;
  float minerals, infrastructure, food;
  
  // Population growth period attributes
  float birthMult, deathMult;   // Births/Deaths per person in a period
  int births, deaths;           // Total Birth/Deaths in a period
  float growthRate;             // Population change per frame
  
  // Food production flags/vars
  bool isOverproducing;
  Uint32 overproductionStartTime;
  
  // Docking flags/vars
  bool playerDocked;
  bool alienDocked;
  Uint32 frameDocked;
  
  // Planet selected flag
  bool selected;
  
  // Decreasing population flag
  bool populationDec;
  
  // Random event flags
  struct {
    bool plague;
    bool blight;
    bool mineCollapse;
  } events;
  
  // MARK: - Helper Methods
  void updateStatus();
  void updateRandomEvents(Uint32 frame);
  void updatePopulation(Uint32 frame);
  void updateMining();
  void updateFarming();
  void updateEventComponent();
  void updateColors();

  SDL_Point uiPosition(SDL_Point p);
  void renderEvents();
};

#endif /* Planet_hpp */
