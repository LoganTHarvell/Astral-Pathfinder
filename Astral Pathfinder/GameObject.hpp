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
  
public:
  GameObject(const char* textureSheet, SDL_Rect src, int x, int y);
  ~GameObject();
  
  void update();
  void render();
  
  void scale(float x);
  
private:
  int xpos;
  int ypos;
  
  SDL_Texture* texture;
  SDL_Rect srcR, destR;

};

#endif /* GameObject_hpp */
