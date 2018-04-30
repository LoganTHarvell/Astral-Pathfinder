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
#include <string>


// MARK: - Game Parameters

namespace GameParameters {

  // Window parameters x, y, w, h
  const SDL_Rect windowRect = { SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                1600, 900 };

  // FPS constants
  const int fps = 60;
  const int frameDelay = 1000/fps;

  const int endgameDelay = 120;

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
    bool restartGame = false;

    enum {
      none, allDiscovered, noFuel, quit
    } endgame = none;

    bool gameOver = false;

    enum {
      inactive, currentOne, currentTwo, selectOne, selectTwo
    } activeSlider = inactive;

    bool clickFlag = false;
    bool planetSelected = false;
    bool playerCollision = false;
    bool alienCollision = false;
    bool mouseDown = false;
    bool debugMode = false;

    // Fields
    Uint32 frame;
    Uint32 startTime;
    Uint32 elapsedTime;
    Uint32 ticks;
    SDL_Point clickLocation;
    SDL_Point dragLocation;
    int mouseScroll = 0;
    Uint32 endgameFrame;
  };

  void init(const std::string title, SDL_Rect rect, bool fullscreen);

  // MARK: - Game Loop Methods
  void handleEvents();
  void update(Uint32 ticks);
  void render();

  // MARK: - Game Methods
  bool running() { return gameState.isRunning; }
  bool restart() { return gameState.restartGame; }
  void clean();
  void restartGame();

  // Global renderer
  static SDL_Renderer *renderer;

private:
  // MARK: - Game Fields
  SDL_Window *window;
  State gameState;

  PlanetManager *planetManager;
  ShipManager *shipManager;
  UIManager *uiManager;

};

#endif /* Game_hpp */
