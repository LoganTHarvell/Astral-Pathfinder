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
  
  // Size helper struct
  struct Size {
    int w, h;
  };
  
public:
  // MARK: - Game Loop Methods
  virtual void update() = 0;
  virtual void render() = 0;
  
  //MARK: - GameObject Methods
  // Get and Set methods for position and size
  SDL_Point getPosition();
  void setPosition(int x, int y);
  Size getSize();
  void scale(float x);
  
protected:
  // MARK: - GameObject Fields
  SDL_Point position;
  Size size;
  SDL_Texture *texture;
  SDL_Rect rect;
  
};

#endif /* GameObject_hpp */
