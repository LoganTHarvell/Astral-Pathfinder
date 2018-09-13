//
//  GameObject.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include "ColliderComponent.hpp"

// TODO: Remove once Game is implemented as a singleton
#include "Game.hpp"

class GameObject {
  
public:
  // MARK: - Game Loop Methods
  virtual void update(Game::State *gs) = 0;
  virtual void render(Game::State *gs) = 0;
  
  //MARK: - GameObject Methods
  ColliderComponent getCollider();
  SDL_Point getPosition();
  void setPosition(SDL_Point p);
  SDL_Rect getRect();
  void scale(float x);
  SDL_Point getCenter();
  
protected:
  // MARK: - GameObject Fields
  SDL_Rect rect;
  SDL_Texture *texture = nullptr;
  ColliderComponent *collider = nullptr;
  
};

#endif /* GameObject_hpp */
