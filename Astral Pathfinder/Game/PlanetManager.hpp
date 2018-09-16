//
//  PlanetManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Manager class responsible for managing all planet gameObjects, specifically
//  initializing, updating, and rendering. Also planet click interactions,
//  planet-ship interactions, docking info, and planet based endgame conditions.

#ifndef PlanetManager_hpp
#define PlanetManager_hpp

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "Game.hpp"
#include "Planet.hpp"
#include "EventsComponent.hpp"


// MARK: - PlanetManager Class

class PlanetManager {

public:
  
  // MARK: - Galaxy Initialization
  void initGalaxy();

  // MARK: - Game Loop Methods
  void update(Game::State *gameState, ShipManager *shipManager);
  void render(Game::State *gameState);

  // MARK: - PlanetManager Methods
  int getTotalPopulation();

  Planet getPlanet(int n);
  Planet getSelectedPlanet();
  bool planetIsDocked();
  bool playerIsDocked();
  bool alienIsDocked();
  Planet getPlayerDockedPlanet();
  Planet getAlienDockedPlanet();
  std::vector<EventsComponent> getEventsList() { return planetEvents; }

  void setPlanetMiningPercent(int p, int flag);
  void setPlanetFarmingPercent(int p, int flag);
  void setPlanetInfraPercent(int p, int flag);
  void setPlanetReservePercent(int p, int flag);

  int fuelDockedShip();

private:
  
  // MARK: - Helper Methods
  
  // Initialiation helper methods
  static Planet initHomeworld();
  static Planet initPlanet();

  void handleClickEvent(SDL_Point p, Game::State *gs);
  void selectPlanet(bool *planetSelected);
  void deselectPlanet(bool *planetSelected);

  void handleCollisions(ShipManager *sm, Uint32 frame);

  // MARK: - PlanetManager Fields
  enum {
    dockedPlanet=1, selectedPlanet
  };

  std::vector<Planet> planets;
  std::vector<EventsComponent> planetEvents;
  int totalPopulation;

  int selectedPlanetIndex;
  int playerDockedPlanetIndex;
  int alienDockedPlanetIndex;
  int discoveryCount;

};

#endif /* PlanetManager_hpp */
