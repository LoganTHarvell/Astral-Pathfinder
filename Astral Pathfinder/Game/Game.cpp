//
//  Game.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Game.hpp"

// MARK: Libraries and Frameworks
#include <iostream>
#include "SDL2_image/SDL_image.h"

// MARK: Source Files
#include "PlanetManager.hpp"
#include "ShipManager.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"
#include "UIManager.hpp"


// MARK: - Game Globals
SDL_Renderer *Game::renderer = nullptr;


// MARK: - Game Initialization

void Game::init(const std::string title, SDL_Rect rect, bool fullscreen) {
  using namespace GameParameters;
  
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
      // Sets render scaling
      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
      SDL_RenderSetLogicalSize(renderer, rect.w, rect.h);
      
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      std::cout << "Renderer created." << std::endl;
    }
    
    gameState.isRunning = true;
    gameState.frame = 0;
    gameState.endgameFrame = 0;
    
    planetManager = new PlanetManager;
    planetManager->initGalaxy();
    
    shipManager = new ShipManager;
    shipManager->init(planetManager->getPlanet(0).getCenter());
    
    uiManager = new UIManager;
    uiManager->init();
    
  }
  else {
    std::cerr << "SDL and/or SDL_image initialization failed, errors: "
              << SDL_GetError() << ", " << IMG_GetError() << std::endl;
  }
}


// MARK: - Game Loop Methods

void Game::handleEvents() {
  SDL_Event event;
  
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        gameState.isRunning = false;
        break;
      case SDL_TEXTINPUT:
        if(gameState.endgame != State::none && gameState.endgame != State::quit
           && SDL_IsTextInputActive()) {
          if(gameState.playerName.length() < 3) {
            gameState.playerName += event.text.text;
            gameState.renderPlayerName = true;
          }
        }
        break;
      case SDL_KEYDOWN:
      {
        if(!uiManager->checkMainMenu() && gameState.endgame == State::none) {
          // Gets pressed key
          SDL_Keycode key = event.key.keysym.sym;
          
          // GameState logic
          if(key == SDLK_ESCAPE && gameState.planetSelected) {
            gameState.planetSelected = false;
          }
          else if (key == SDLK_d) {
            gameState.debugMode = !gameState.debugMode;
          }
        }
        else if(gameState.endgame != State::none && gameState.endgame != State::quit
                && SDL_IsTextInputActive()) {
          SDL_Keycode key = event.key.keysym.sym;
          if(key == SDLK_BACKSPACE && gameState.playerName.length() > 0) {
            gameState.playerName.pop_back();
            gameState.renderPlayerName = true;
          }
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
        gameState.mouseDown = true;
        gameState.clickLocation = { event.button.x, event.button.y };
        break;
      case SDL_MOUSEMOTION:
        // TODO: Verify this doesn't need to be changes to gameState.gameOver
        if(uiManager->checkMainMenu() || uiManager->checkScoreboardScreen() ||
           (gameState.endgame != State::none && gameState.endgame != State::quit))
          gameState.dragLocation = { event.motion.x, event.motion.y };
        
        else if(gameState.planetSelected || gameState.planetCollided)
          gameState.dragLocation = { event.motion.x, event.motion.y };
        break;
      case SDL_MOUSEBUTTONUP:
        gameState.clickFlag = true;
        gameState.clickLocation = { event.button.x, event.button.y };
        gameState.mouseDown = false;
        gameState.activeSlider = State::inactive;
        break;
      case SDL_MOUSEWHEEL:
        if(event.wheel.y > 0 || event.wheel.y < 0) {
          gameState.mouseScroll = event.wheel.y;
        }
      default:
        break;
    }
  }
  
}

void Game::update(Uint32 ticks) {
  if (gameState.endgame != State::none) {
    if (gameState.endgameFrame == 0) {
      gameState.endgameFrame = gameState.frame + GameParameters::endgameDelay;
    }
    else if (gameState.frame > gameState.endgameFrame) {
      gameState.gameOver = true;
    }
  }
  
  if (!uiManager->checkMainMenu() && !gameState.gameOver) {
    if (gameState.frame == 0) gameState.startTime = SDL_GetTicks()/1000;
    
    gameState.frame++;
    gameState.elapsedTime = (SDL_GetTicks()/1000) - gameState.startTime;
    gameState.ticks = ticks;
  
    planetManager->update(&gameState, shipManager);
    shipManager->update(&gameState, planetManager);
  }
    
  
  uiManager->update(&gameState, planetManager, shipManager);
  
  if(gameState.restartGame)
    restartGame();
}

void Game::render() {
  using GameParameters::windowRect;

  SDL_RenderClear(renderer);
  
  // Render stuff
  uiManager->render(&gameState, planetManager);
  
  if(!uiManager->checkMainMenu() && !uiManager->checkScoreboardScreen()
     && gameState.endgame == State::none) {
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
  
  std::cout << "Game cleaned." << std::endl;
}

void Game::restartGame() {
  delete planetManager;
  delete shipManager;
  delete uiManager;
  
  planetManager = new PlanetManager;
  planetManager->initGalaxy();
  
  shipManager = new ShipManager;
  shipManager->init(planetManager->getPlanet(0).getCenter());
  
  uiManager = new UIManager;
  uiManager->init();
  
  gameState.restartGame = false;
  if(gameState.skipMainMenu) {
    uiManager->setMainMenuFlag(false);
    gameState.skipMainMenu = false;
  }
  gameState.playerName = "";
}
