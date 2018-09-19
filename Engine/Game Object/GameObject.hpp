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


// MARK: - GameObject Class

class GameObject {
  
public:
  
  // MARK: - Initialization Methods
  
  void init(SDL_Rect rect, int rotation, SDL_Texture *texture);
  
  // MARK: - Game Loop Methods
  
  void update();
  void render(SDL_Renderer *renderer);
  
  //MARK: - GameObject Methods
  
  SDL_Point getPosition();
  SDL_Rect getRect();
  int getRotation();
  SDL_Point getCenter();
  ColliderComponent getCollider();
  
protected:
  
  // MARK: - GameObject Fields
  
  SDL_Rect rect;
  int rotation;
  SDL_Texture *texture = nullptr;
  ColliderComponent *collider = nullptr;

  // MARK: - Helper Methods

  void setPosition(SDL_Point p);
  
  void scale(float x);

};

#endif /* GameObject_hpp */
