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
#include "GameObject.hpp"
#include "Map.hpp"
#include "TextureManager.hpp"


SDL_Renderer *Game::renderer = nullptr;

// MARK: - Game Initialization

void Game::init(const char *title,
                int x, int y, int w, int h, bool fullscreen) {
  
  int flags = 0;
  int imgFlags = IMG_INIT_PNG;
  
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  
  // Initializes SDL frameworks
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0
      && ( IMG_Init( imgFlags ) & imgFlags )) {
    std::cout << "SDL and SDL_image initialised!..." << std::endl;
    
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
      SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);
      
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
//  map = new Map();
//  map->loadPlanets(planetManager->planets);
//  map->loadShip();
}


// MARK: - Game Functions

void Game::handleEvents() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
    case SDL_QUIT:
      isRunning = false;
      break;
    default:
      break;
  }
  
}

void Game::update() {
  planetManager->update();
//  map->update();
}

void Game::render() {
  SDL_RenderClear(renderer);
  
  SDL_RenderCopy(renderer, gameScreen, NULL, NULL);

  // Render stuff
  planetManager->render();
//  map->render();
//  shipManager->render();

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  IMG_Quit();
  
  std::cout << "Game cleaned." << std::endl;
}
