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


SDL_Renderer *Game::renderer = nullptr;


// MARK: - Game Initialization

void Game::init(const char *title,
                int x, int y, int w, int h, bool fullscreen) {
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
    window = SDL_CreateWindow(title, x, y, w, h, flags | SDL_WINDOW_RESIZABLE );
    if (window) {
      std::cout << "Window created." << std::endl;
    }
    
    // Initializes renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      // Sets render scaling
      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
      SDL_RenderSetLogicalSize(renderer, windowSize.w, windowSize.h);
      
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      std::cout << "Renderer created." << std::endl;
    }
    
    isRunning = true;
    
  } else {
    isRunning = false;
    std::cerr << "SDL and/or SDL_image initialization failed, errors: "
              << SDL_GetError() << ", " << IMG_GetError() << std::endl;
  }

  // Initializes game screen
  gameScreen = TextureManager::loadTexture("Resources/Assets/gameScreen.png");
  
  planetManager = new PlanetManager;
  planetManager->initGalaxy();

  shipManager = new ShipManager;
  shipManager->init(planetManager->getPlanet(0).getCenter());
  
  uiManager = new UIManager;
  uiManager->init();
}


// MARK: - Game Loop Methods

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    case SDL_KEYDOWN:
      shipManager->shipMovement(event);
      break;
    case SDL_KEYUP:
      if(event.key.keysym.sym == SDLK_ESCAPE && clickFlag) {
        clickFlag = false;
        uiManager->resetSelectedPlanet();
        planetManager->revertClick();
      }
      else
        shipManager->shipMovement(event);
      break;
    case SDL_MOUSEBUTTONUP:
      clickFlag = planetManager->checkClicked(event, uiManager, clickFlag);
      break;
    default:
      break;
  }
  
}

void Game::update(Uint32 ticks) {
  planetManager->update(shipManager);
  shipManager->update(ticks);
}

void Game::render() {
  SDL_RenderClear(renderer);
  
  using GameParameters::windowSize;
  SDL_Rect windowR = { 0, 0, windowSize.w, windowSize.h };
  SDL_RenderCopy(renderer, gameScreen, NULL, &windowR);

  // Render stuff
  planetManager->render();
  shipManager->render();
  if(clickFlag)
    uiManager->render();

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
