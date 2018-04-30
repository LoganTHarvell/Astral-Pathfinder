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
  
  const std::string movingPlayerTex = "../Resources/movingPlayerShip.png";
  
  const struct {
    int w = 48, h = 24;
  } shipSize;
  
  const int totalCrew = 1000;
  
  // TODO: figure out real velocity/ticks formula
  const int speed = 1;
  const int turnSpeed = 5;
}


// MARK: - Ship Class

class Ship: public GameObject {
  
public:
  // MARK: - Initialization Methods
  virtual void init(SDL_Point startPosition) = 0;
  
  // MARK: - Game Loop Methods
  void update(Game::State *gs);
  void render(Game::State *gs);
  
  // MARK: - Ship Methods
  int getRotation() { return rotation; };
  SDL_Point getVelocity() { return velocity; }
  SDL_Point getUIPosition() { return getCenter(); };
  SDL_Point mapPosition();
    
protected:
  using PointVector = std::vector<SDL_Point>;

  // MARK: - Ship Fields  
  SDL_Point velocity;
  int rotation;
  
  // MARK: - Helper Methods
  bool boundaryCollision();
  
  virtual PointVector shipVertexVectors() = 0;
  PointVector computeShipVertices();
  
  virtual void updateVelocity() = 0;
  
  void updateRotation();
  void updatePosition(Uint32 ticks);

};

#endif /* Ship_hpp */
