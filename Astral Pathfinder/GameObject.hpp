//
//  GameObject.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

class GameObject {
  
  struct Coordinates {
    int x, y;
  };
  
  struct Size {
    int w, h;
  };
  
public:
  GameObject(const char* textureSheet, SDL_Rect src, int x, int y);
  ~GameObject();
  
  void update();
  void render();
  
  void setPosition(int x, int y);
  Coordinates getPosition();
  Size getSize();
  void scale(float x);
  
private:
  Coordinates position;
  Size size;
  
  SDL_Texture* texture;
  SDL_Rect srcR, destR;

};

#endif /* GameObject_hpp */
