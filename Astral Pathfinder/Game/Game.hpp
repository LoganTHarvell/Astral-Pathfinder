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
class PlanetManager;
class ShipManager;
class Map;

class Game {
  
public:
  void init(const char *title, int x, int y, int w, int h, bool fullscreen);
  
  // MARK: Game Loop Methods
  void handleEvents();
  void update();
  void render();
  
  // MARK: Game Methods
  bool running() { return isRunning; };
  void clean();

  // Global renderer
  static SDL_Renderer *renderer;
  
private:
  // MARK: Game Fields
  bool isRunning = false;
  SDL_Window *window;
  
  SDL_Texture *gameScreen;
  PlanetManager *planetManager;
  ShipManager *shipManager;
  Map *map;
  
};

#endif /* Game_hpp */
