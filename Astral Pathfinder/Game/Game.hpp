//
//  Game.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "parameters.h"

// MARK: Parameter Constants
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900


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
  
private:
  bool isRunning = false;
  SDL_Window *window;
  
  GameObject *gameScreen;
  Galaxy *galaxy;
  Map *map;
  
public:
  void handleEvents();
  void update();
  void render();
  void clean();
  
  bool running() { return isRunning; };
  
  static SDL_Renderer *renderer;
  
};

#endif /* Game_hpp */
