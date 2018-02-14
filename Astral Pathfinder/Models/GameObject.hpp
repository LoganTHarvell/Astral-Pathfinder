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
  
  struct Size {
    int w, h;
  };
  
public:
  virtual void update() = 0;
  virtual void render() = 0;
  
  // Get and Set functions for position and size
  SDL_Point getPosition();
  void setPosition(int x, int y);
  Size getSize();
  void scale(float x);
  
protected:
  SDL_Point position;
  Size size;
  
  SDL_Texture *texture;
  SDL_Rect srcR = { 0, 0, NULL, NULL };
  SDL_Rect destR = srcR;
  
};

#endif /* GameObject_hpp */
