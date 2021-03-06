//
//  AlienShip.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 4/29/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//
//  Description:
//  Class extension of Ship base class for modeling an AI enemy. Handles path
//  planning and velocity calculations, as well as calculating vertex vectors.
//  Also handles initializing and updating.

#ifndef AlienShip_hpp
#define AlienShip_hpp

// MARK: Parent Class
#include "Ship.hpp"


class AlienShip : public Ship {

public:
  void init(SDL_Point startPosition);
  
  void update(Game::State *gs);

  void setMainTarget(SDL_Point p);
  SDL_Point getMainTarget() { return mainTarget; };
  SDL_Point getTarget() { return target; };
  
  void resetTarget();
  void updateTarget(SDL_Point p);
  
private:

  SDL_Point mainTarget;
  SDL_Point target;
  
  // MARK: - Helper Methods
  PointVector shipVertexVectors();
  
  void updateVelocity();
};

#endif /* AlienShip_hpp */
