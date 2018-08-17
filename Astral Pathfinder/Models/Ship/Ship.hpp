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


// MARK: - Ship Class

class Ship: public GameObject {
  
public:
  // MARK: - Initialization Methods
  virtual void init(SDL_Point startPosition) = 0;
  
  // MARK: - Game Loop Methods
  virtual void update(Game::State *gs) = 0;
  void render(Game::State *gs);
  
  // MARK: - Ship Methods
  // TODO: Make ship tags a class owned enum
  Parameters::Ship::ShipType getTag() { return tag; };
  int getRotation() { return rotation; };
  SDL_Point getVelocity() { return velocity; }
  SDL_Point getUIPosition() { return getCenter(); };
  SDL_Point mapPosition();
    
protected:
  using PointVector = std::vector<SDL_Point>;

  // MARK: - Ship Fields
  Parameters::Ship::ShipType tag;
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
