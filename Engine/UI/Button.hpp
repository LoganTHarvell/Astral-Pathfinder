//
//  Button.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  A UI element that represents a on/off state through a clickable box. This
//  class handles initializing, updating, and rendering the button.

#ifndef Button_hpp
#define Button_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include "TextureManager.hpp"


// MARK - Button Class

class Button {

public:
 
  // MARK: - Initialization Methods
  
  void init(SDL_Rect text, SDL_Rect outline, int screen,
            std::string textureFile, SDL_Renderer *renderer);
  
  // MARK: - Game Loop Methods
  
  void update();
  void render(SDL_Renderer *renderer);
  
  // Mark: - Button Methods
  
  bool checkInBounds(SDL_Point p);
  void checkIfHovering(SDL_Point dragLocation);
  bool checkClick(SDL_Point p);
  
  int getID() { return id; }
  
private:
  
  // MARK: - Button Fields
 
  int id;
  SDL_Rect bounds, border;
  bool isActive;
  SDL_Texture *texture = nullptr;

};

#endif /* Button_hpp */
