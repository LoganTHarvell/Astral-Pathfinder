//
//  Game.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/14/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "parameters.h"

// UI constants
#define BORDER_WIDTH 6
#define WINDOW_WIDTH 1400 + (BORDER_WIDTH * 3)
#define WINDOW_HEIGHT 1000 + (BORDER_WIDTH * 2)
#define MAP_WIDTH 1000
#define MAP_HEIGHT MAP_WIDTH
#define INFO_WIDTH 400
#define INFO_HEIGHT (MAP_HEIGHT/2) - (BORDER_WIDTH/2)
#define MAP_X_ORIGIN 0 + BORDER_WIDTH
#define MAP_Y_ORIGIN 0 + BORDER_WIDTH
#define INFO_X_ORIGIN MAP_X_ORIGIN + MAP_WIDTH + BORDER_WIDTH
#define INFO_Y_ORIGIN MAP_Y_ORIGIN
#define INFO2_Y_ORIGIN MAP_Y_ORIGIN + INFO_HEIGHT + BORDER_WIDTH

// FPS constants
#define FPS 60
#define FRAME_DELAY 1000/FPS

class GameObject;
class Galaxy;

class Game {
  
public:
  Game();
  ~Game();
  
  void init(const char *title, int x, int y, int w, int h, bool fullscreen);
  void handleEvents();
  void update();
  void render();
  void clean();
  
  bool running() { return isRunning; };
  
  static SDL_Renderer* renderer;
  
private:
  bool isRunning = false;
  SDL_Window *window;
  
  Galaxy* galaxy;
  
  GameObject* ship;
};



#endif /* Game_hpp */
