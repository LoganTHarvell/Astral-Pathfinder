//
//  GameObject.hpp
//  SDL_Test
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "SDL2/SDL.h"

class GameObject {
  
public:
  GameObject(const char* textureSheet, SDL_Rect src, int x, int y);
  ~GameObject();
  
  void update();
  void render();
  
private:
  int xpos;
  int ypos;
  
  SDL_Texture* texture;
  SDL_Rect srcR, destR;

};

#endif /* GameObject_hpp */
