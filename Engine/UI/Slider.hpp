//
//  Slider.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 3/3/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  A UI element that represents a ratio through a slider along a base. This
//  class handles initializing, updating, and rendering the slider. It also
//  enables getting and setting the attributes like position and corresponding
//  percentage.

#ifndef Slider_hpp
#define Slider_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include <string>


// MARK: - Slider Class

class Slider {

public:
  
  // MARK: - Initialization Methods
  
  void init(SDL_Rect base, SDL_Rect circ);
  
  // MARK: - Game Loop Methods
  
  void update();
  void render(SDL_Renderer *renderer);
  void clean();
  
  // MARK: - Slider Methods
  
  bool isInitialized();
  void setTextures(std::string baseFile, std::string sliderFile,
                   SDL_Renderer *renderer, int percent);
  void colorMod(SDL_Color base, SDL_Color slider);
  SDL_Rect getBaseRect() { return base; }
  SDL_Rect getSliderRect() { return slider; }
  SDL_Point getSliderPosition() { return { slider.x, slider.y }; };
  void setSliderPosition(int pos);
  int getPercent();
  void updateSliderPosition(int percent);
  
private:
  
  // MARK: - Slider Fields
  
  SDL_Rect base, slider;
  SDL_Texture *baseTexture = nullptr, *sliderTexture = nullptr;

};


#endif /* Slider_hpp */
