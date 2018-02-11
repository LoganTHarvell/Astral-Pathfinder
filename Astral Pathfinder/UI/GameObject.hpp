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


class GameObject {
  
public:
  GameObject(const char *textureSheet, SDL_Rect src, int x, int y);
  ~GameObject();
  
private:
  SDL_Point position;
  struct Size {
    int w, h;
  } size;
  
  SDL_Texture *texture;
  SDL_Rect srcR, destR;

public:
  void update();
  void render();
  
  // Get and Set functions for position and size
  SDL_Point getPosition() { return position; };
  void setPosition(int x, int y) { position.x = x; position.y = y; };
  Size getSize() { return size; };
  void scale(float x) { size.w *= x; size.h *= x; };
  
};

#endif /* GameObject_hpp */
