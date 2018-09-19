//
//  Game.cpp
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

// MARK: Header File
#include "Game.hpp"

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "SDL2_image/SDL_image.h"
#include <iostream>
#include "TextureManager.hpp"

// MARK: Source Files
#include "PlanetManager.hpp"
#include "ShipManager.hpp"
#include "UIManager.hpp"

// MARK: Namespaces
using namespace Parameters::Game;

// MARK: Game Globals
SDL_Renderer *Game::renderer = nullptr;


// MARK: - Game Initialization
void Game::init(const std::string title, SDL_Rect rect, bool fullscreen) {
    
  // Seeds random number generator
  srand((unsigned)time(NULL));
  
  int flags = 0;
  
  int imgFlags = IMG_INIT_PNG;
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  
  // Initializes SDL frameworks
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0
      && ( IMG_Init( imgFlags ) & imgFlags ) && TTF_Init() == 0) {
    std::cout << "Frameworks initialised!..." << std::endl;
    
    // Initializes window
    window = SDL_CreateWindow(title.c_str(), rect.x, rect.y, rect.w, rect.h,
                              flags | SDL_WINDOW_RESIZABLE);
    if (window) {
      std::cout << "Window created." << std::endl;
    }
    
    // Initializes renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      // Enables and configures render scaling
      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
      SDL_RenderSetLogicalSize(renderer, rect.w, rect.h);
      
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      std::cout << "Renderer created." << std::endl;
    }

    // Update appropriate game state values
    gameState.isRunning = true;
    gameState.frame = 0;
    gameState.endgameFrame = 0;
    
    // Create sub-level managers
    planetManager = new PlanetManager;
    planetManager->initGalaxy();
    
    shipManager = new ShipManager;
    shipManager->init(planetManager->getPlanet(0).getCenter(),
                      planetManager->getPlanet(1).getCenter());
    
    uiManager = new UIManager;
    uiManager->init(&gameState);
    
  }
  else {
    std::cerr << "SDL and/or SDL_image initialization failed, errors: "
              << SDL_GetError() << ", " << IMG_GetError() << std::endl;
  }
}


// MARK: - Game Loop Methods

// TODO: Clean up event handler, make modular, remove dependencies
// Method for polling and evaluting events, sets appropriate game states
void Game::handleEvents() {
  SDL_Event event;
  
  // Polls for events
  while (SDL_PollEvent(&event)) {
    
    // Evaluates event
    switch (event.type) {
      case SDL_QUIT:
      {
        
        gameState.isRunning = false;
        
        break;
      }
      case SDL_TEXTINPUT:
      {
        
        // Text input enabled upon game over
        if (gameState.endgame != State::none
            && gameState.endgame != State::quit
            && SDL_IsTextInputActive()) {
          
          // Limits player name length, update appropriate gamestate values
          if (gameState.playerName.length() < 3) {
            gameState.playerName += event.text.text;
            gameState.renderPlayerName = true;
          }
        
        }
        
        break;
      }
      case SDL_KEYDOWN:
      {
        
        // Gets pressed key
        SDL_Keycode key = event.key.keysym.sym;
  
        // Enables hot reloading of parameters
        // TODO: Create hot reload methods for appropriate values
        if (uiManager->getActiveScreen() != Screen::ID::scores
            && key == SDLK_h) {
          Parameters::loadParameters();
          SDL_SetWindowPosition(window, windowRect.x, windowRect.y);
          SDL_SetWindowSize(window, windowRect.w, windowRect.h);
        }

        // Evaluates keydown events associated with gameplay
        if (!uiManager->checkStartScreens() && gameState.endgame == State::none) {
          
          // Planet Deselection
          if (key == SDLK_ESCAPE && gameState.planetSelected) {
            gameState.planetSelected = false;
          }
          // Debug Mode
          else if (key == SDLK_d) {
            gameState.debugMode = !gameState.debugMode;
          }
          
        }
        // Evaluates keydown events associated with player name input
        else if (gameState.endgame != State::none
                 && gameState.endgame != State::quit
                 && SDL_IsTextInputActive()) {
          
          // Enables backspace during player name input
          if (key == SDLK_BACKSPACE && gameState.playerName.length() > 0) {
            gameState.playerName.pop_back();
            gameState.renderPlayerName = true;
          }
        }
        
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
      {
        
        // Updates click game state information
        gameState.mouseDown = true;
        gameState.clickLocation = { event.button.x, event.button.y };
        
        break;
      }
      case SDL_MOUSEMOTION:
      {
        
        // Updates drag location following a click during start and endgame
        if (uiManager->checkStartScreens()
            || (gameState.endgame != State::none
                && gameState.endgame != State::quit)) {
              
          gameState.dragLocation = { event.motion.x, event.motion.y };
        
        }
        // Updates drag location during gameplay when a slider is visible
        else if (gameState.planetSelected || gameState.playerCollision)
          gameState.dragLocation = { event.motion.x, event.motion.y };
        
        break;
      }
      case SDL_MOUSEBUTTONUP:
      {
        
        // Updates click game state information
        gameState.clickFlag = true;
        gameState.clickLocation = { event.button.x, event.button.y };
        gameState.mouseDown = false;
        gameState.activeSlider = State::inactive;
       
        break;
      }
      case SDL_MOUSEWHEEL:
      {
        
        // Updates scrolling game state information
        if (event.wheel.y > 0 || event.wheel.y < 0) {
          gameState.mouseScroll = event.wheel.y;
        }
        
        break;
      }
      default:
        break;
    }
  }
  
}

// Updates game state and all sub-level managers for each new frame
void Game::update(Uint32 ticks) {
  
  // During endgame, update game state for endgame delay and gameover
  if (gameState.endgame != State::none) {
    
    if (gameState.endgameFrame == 0) {
      gameState.endgameFrame = gameState.frame + Parameters::Game::endgameDelay;
    }
    else if (gameState.frame > gameState.endgameFrame) {
      gameState.gameOver = true;
    }
  
  }
  
  // During gameplay, update game state
  if (!uiManager->checkStartScreens() && !gameState.gameOver) {
    
    // Calculates gameplay start time at frame 0
    if (gameState.frame == 0) gameState.startTime = SDL_GetTicks()/1000;
    
    // Updates frame, time, ticks
    gameState.frame++;
    gameState.elapsedTime = (SDL_GetTicks()/1000) - gameState.startTime;
    gameState.ticks = ticks;
  
    // Calls sub-level managers to update
    planetManager->update(&gameState, shipManager);
    shipManager->update(&gameState, planetManager);
  }
    
  // Calls sub-level managers to update
  uiManager->update(&gameState, planetManager, shipManager);
  
  if (gameState.restartGame) restartGame();

}

// Renders all game elements
void Game::render() {
  using Parameters::Game::windowRect;

  // Clears screen
  SDL_RenderClear(renderer);
  
  // Calls sub-level manager to render UI
  uiManager->render(&gameState, planetManager);
  
  // During gameplay, call sub-level managers to render gameplay elements
  if (!uiManager->checkStartScreens()
      && (gameState.endgame == State::none || !gameState.gameOver)
      && gameState.endgame != State::quit) {
    planetManager->render(&gameState);
    shipManager->render(&gameState);
  }

  SDL_RenderPresent(renderer);
  
}


// MARK: - Game Methods

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
  
  delete planetManager;
  delete shipManager;
  delete uiManager;
  
  std::cout << "Game cleaned." << std::endl;
}

void Game::restartGame() {
  delete planetManager;
  delete shipManager;
  delete uiManager;
  
  planetManager = new PlanetManager;
  planetManager->initGalaxy();
  
  shipManager = new ShipManager;
  shipManager->init(planetManager->getPlanet(0).getCenter(),
                    planetManager->getPlanet(1).getCenter());
  
  uiManager = new UIManager;
  uiManager->init(&gameState);
  
  gameState.restartGame = false;
  gameState.skipMainMenu = false;
  gameState.playerName = "";
  gameState.planetSelected = false;
}
