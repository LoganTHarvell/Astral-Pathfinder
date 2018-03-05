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


// MARK: - Game Parameters

namespace GameParameters {

  const struct {
    int w = 1600;
    int h = 900;
  } windowSize;
  
  // FPS constants
  const int fps = 60;
  const int frameDelay = 1000/fps;

}


// MARK: - Game Class

// Forwards classes in Game class
class GameObject;
class PlanetManager;
class ShipManager;
class UIManager;

class Game {
  
public:
  // Data structure for keeping track of the game state
  struct State {
    // Flags
    bool isRunning = false;
    bool clickFlag = false;
    bool planetSelected = false;
    
    bool debugMode = false;
    
    // Fields
    SDL_Point clickLocation;
  };
  
  void init(const char *title, int x, int y, int w, int h, bool fullscreen);
  
  // MARK: - Game Loop Methods
  void handleEvents();
  void update(Uint32 ticks);
  void render();
  
  // MARK: - Game Methods
  bool running() { return gameState.isRunning; };
  void clean();

  // Global renderer
  static SDL_Renderer *renderer;
  
private:
  // MARK: - Game Fields
  SDL_Window *window;
  State gameState;

  SDL_Texture *gameScreen;
  PlanetManager *planetManager;
  ShipManager *shipManager;
  UIManager *uiManager;
  
};

#endif /* Game_hpp */
