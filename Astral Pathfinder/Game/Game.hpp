//
//  Game.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Highest level manager class responsible for managing the game state and
//  all game elements through sub-level manager classes. Responsibilities
//  include initialization and all game loop methods, specifically event
//  handling, updating, and rendering.

#ifndef Game_hpp
#define Game_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include <string>

// Forwards classes in Game class
class GameObject;
class PlanetManager;
class ShipManager;
class UIManager;


// MARK: - Game Class
// TODO: Reimplement as a singleton
class Game {

public:
  
  // MARK: - Game State
  
  struct State {
    
    // Game loop flags
    bool isRunning = false;
    bool skipMainMenu = false;
    bool gameOver = false;
    bool restartGame = false;
  
    // Endgame states
    enum {
      none, allDiscovered, noFuel, alienAttack, quit
    } endgame = none;

    // Event Handling Flags
    bool clickFlag = false;
    bool planetSelected = false;
    bool playerCollision = false;
    bool alienCollision = false;
    bool mouseDown = false;
    bool debugMode = false;

    // Slider states
    enum {
      inactive, resourceSlider, depositSlider
    } activeSlider = inactive;
    
    // Game State Values
    Uint32 frame;
    Uint32 startTime;
    Uint32 elapsedTime;
    Uint32 ticks;
    SDL_Point clickLocation;
    SDL_Point dragLocation;
    int mouseScroll = 0;
    std::string playerName;
    bool renderPlayerName = false;
    Uint32 endgameFrame;
  };

  // MARK: - Game Initialization Methods
  
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
