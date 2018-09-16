//
//  GameObject.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Base class for creating a game object. Enabling the initialization,
//  update, and render of an entity to the screen with a bounding rectangle.
//  Also manages getters and setters for basic information about the object.

#ifndef GameObject_hpp
#define GameObject_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include "ColliderComponent.hpp"

// TODO: Remove once Game is implemented as a singleton
#include "Game.hpp"


// MARK: - GameObject Class

class GameObject {
  
public:
  
  // MARK: - Game Loop Methods
  
  // TODO: Implement for a base gameObject, override in sub-classes
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
