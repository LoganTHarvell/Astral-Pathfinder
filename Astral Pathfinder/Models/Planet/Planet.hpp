//
//  Planet.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  A GameObject class extension for modeling the Planet game element. Contains
//  and manages an individual planet's state and resources. Planet state
//  includes ship-docking using collision information from collider componenet.
//  Resources update according to a growth period cycle system over many frames.
//  Also handles initializing, updating, and rendering.

#ifndef Planet_hpp
#define Planet_hpp

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include "GameObject.hpp"

// MARK: Source Files
#include "Game.hpp"
#include "EventsComponent.hpp"


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

  // TODO: Change to resource component system
  // Possibly split into mining, farming, and population components
  
  // TODO: Rework events component to reduce coupling
  EventsComponent *eventManager = nullptr;

  SDL_Texture *outlineTexture = nullptr;
  SDL_Rect outlineRect;

  // Resources
  float population, populationCheck;
  float deposits, fertility;
  int miningPercent, farmingPercent, infraPercent, reservePercent;
  float minerals, infrastructure, food;
  
  // Population growth period attributes
  float birthMult, deathMult;   // Births and Deaths per person in a period
  int births, deaths;           // Total Birth and Deaths in a period
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
