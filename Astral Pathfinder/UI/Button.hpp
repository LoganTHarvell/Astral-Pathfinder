//
//  Button.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Button_hpp
#define Button_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "TextureManager.hpp"
#include "Game.hpp"


// MARK - Button Class

class Button {
public:
  // MARK: - Initialization Methods
  void init(SDL_Rect text, SDL_Rect outline, int screen);
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  
  // Mark: - Button Methods
  bool checkInBounds(SDL_Point p);
  void checkIfHovering(Game::State *gs);
  bool checkClick(SDL_Point p);
  int getNextScreen() { return nextScreen; }
  
  
private:
  SDL_Rect bounds, border;
  bool isActive;
  SDL_Texture *texture = TextureManager::loadTexture("../Resources/border.png");
  int nextScreen;
};

#endif /* Button_hpp */
