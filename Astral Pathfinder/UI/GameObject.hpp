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
  void update();
  void render();
  
  // Get and Set functions for position and size
  SDL_Point getPosition() { return position; };
  void setPosition(int x, int y) { position.x = x; position.y = y; };
  Size getSize() { return size; }
  void scale(float x) { size.w *= x; size.h *= x; };
  
protected:
  SDL_Point position;
  Size size;
  
  SDL_Texture *texture;
  SDL_Rect srcR = { 0, 0, NULL, NULL };
  SDL_Rect destR = srcR;
  
};

#endif /* GameObject_hpp */
