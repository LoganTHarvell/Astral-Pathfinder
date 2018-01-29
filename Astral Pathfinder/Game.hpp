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

// MARK: Parameter Constants
// UI constants
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
#define MAP_WIDTH 800
#define MAP_HEIGHT 800
#define MAP_X_ORIGIN 400
#define MAP_Y_ORIGIN 50
#define INFO_X_ORIGIN 0
#define INFO_Y_ORIGIN 0
#define INFO2_Y_ORIGIN 0

// FPS constants
#define FPS 60
#define FRAME_DELAY 1000/FPS


class GameObject;
class Galaxy;
class Map;

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
  
  GameObject* gameScreen;
  Galaxy* galaxy;
  Map* map;
};



#endif /* Game_hpp */
