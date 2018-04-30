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
  
  void setTarget(SDL_Point p);
  
private:
  
  SDL_Point target;
  
  // MARK: - Helper Methods
  PointVector shipVertexVectors();

  void updateVelocity();
};

#endif /* AlienShip_hpp */
