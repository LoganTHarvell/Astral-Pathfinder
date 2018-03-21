//
//  Ship.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include <string>

// MARK: Source Files
#include "GameObject.hpp"


// MARK: - Ship Parameters

namespace ShipParameters {
  
  enum ShipType {
    playerShip,
    alienWarship
  };
  
  const std::string movingPlayerTex = "Resources/Assets/movingPlayerShip.png";
  
  const struct {
    int w = 48, h = 24;
  } shipSize;
  
  const int shipPopulation = 1000;
  
  // TODO: figure out real velocity/ticks formula
  const int speed = 1;
  const int turnSpeed = 5;
}


// MARK: - Ship Class

class Ship: public GameObject {
  using PointVector = std::vector<SDL_Point>;
  
public:
  // MARK: - Initialization Methods
  void init(SDL_Point startPosition, ShipParameters::ShipType type);
  
  // MARK: - Game Loop Methods
  void update(Game::State *gs);
  void render(Game::State *gs);
  
  // MARK: - Ship Methods
  ShipParameters::ShipType getTag() { return tag; };
  int getFuel() { return fuel; };
  int getPopulation() { return population; };
  int getRotation() { return rotation; };
  SDL_Point getUIPosition() { return getCenter(); };
  SDL_Point getMapPosition(SDL_Point uiPosition);
  
private:
  // MARK: - Ship Fields
  ShipParameters::ShipType tag;
  int population;
  int fuel;
  
  SDL_Point velocity;
  int rotation;
  
  // MARK: - Helper Methods
  bool boundaryCollision();
  PointVector shipVertexVectors();
  PointVector computeShipVertices();
  
  void updateVelocity();
  void updateRotation();
  void updatePosition(Uint32 ticks);
  void updateFuel(int minerals);

};

#endif /* Ship_hpp */
