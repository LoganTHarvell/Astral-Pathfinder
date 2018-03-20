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
    
    // Object Initialization
    gameScreen = TextureManager::loadTexture("Resources/Assets/gameScreen.png");
    screenRect = { 0, 0, windowRect.w, windowRect.h };
    
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
      case SDL_KEYDOWN:
      {
        // Gets pressed key
        SDL_Keycode key = event.key.keysym.sym;
        
        // GameState logic
        if(key == SDLK_ESCAPE && gameState.planetSelected) {
          gameState.planetSelected = false;
        }
        else if (key == SDLK_d) {
          gameState.debugMode = !gameState.debugMode;
        }
        
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
        gameState.mouseDown = true;
        gameState.clickLocation = { event.button.x, event.button.y };
        break;
      case SDL_MOUSEMOTION:
        if(gameState.planetSelected || gameState.planetCollided)
          gameState.dragLocation = { event.motion.x, event.motion.y };
        break;
      case SDL_MOUSEBUTTONUP:
        gameState.clickFlag = true;
        gameState.clickLocation = { event.button.x, event.button.y };
        gameState.mouseDown = false;
        gameState.activeSlider = State::inactive;
        break;
      default:
        break;
    }
  }
  
}

void Game::update(Uint32 ticks) {
  gameState.ticks = ticks;
  
  if (!gameState.mainMenu || gameState.endgame == State::none) {
    planetManager->update(&gameState, shipManager);
    shipManager->update(&gameState);
  }
  
  uiManager->update(&gameState, planetManager, shipManager);
}

void Game::render() {
  using GameParameters::windowRect;

  SDL_RenderClear(renderer);
  
  // Render stuff
  if (!gameState.mainMenu || gameState.endgame == State::none) {
    SDL_RenderCopy(renderer, gameScreen, NULL, &screenRect);
    planetManager->render(&gameState);
    shipManager->render(&gameState);
  }
  
  uiManager->render(&gameState, planetManager);

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
