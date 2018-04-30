//
//  AlienShip.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 4/29/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#ifndef AlienShip_hpp
#define AlienShip_hpp

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
  
  const std::string alienTex = "../Resources/alienShip.png";
  
  
  // MARK: - Helper Methods
  PointVector shipVertexVectors();
  
  void updateVelocity();
};

#endif /* AlienShip_hpp */
