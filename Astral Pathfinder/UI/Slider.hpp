//
//  Slider.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 3/3/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Slider_hpp
#define Slider_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "Game.hpp"
#include "Planet.hpp"


// MARK: - Slider Class

class Slider {
public:
  // MARK: - Initialization Methods
  void init(SDL_Rect base, SDL_Rect circ);
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  void clean();
  
  // MARK: - Slider Methods
  void setTextures(int percent);
  SDL_Rect getBasePosition() { return base; }
  SDL_Rect getCirclePosition() { return circle; }
  int setCirclePosition(int pos);
  
private:
  // MARK: - Slider Fields
  SDL_Rect base, circle;
  SDL_Texture *bar, *circ;
  bool setPos = false;
};


#endif /* Slider_hpp */
