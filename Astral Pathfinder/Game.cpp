//
//  Game.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/14/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

// MARK: Header File
#include "Game.hpp"

// MARK: Libraries and Frameworks
#include <iostream>
#include "SDL2_image/SDL_image.h"

// MARK: Source Files
#include "Map.hpp"
#include "GameObject.hpp"

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char * title,
                int x, int y, int w, int h, bool fullscreen) {
  
  int flags = 0;
  int imgFlags = IMG_INIT_PNG;
  
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0
      && ( IMG_Init( imgFlags ) & imgFlags )) {
    std::cout << "SDL and SDL_image initialised!..." << std::endl;
    
    window = SDL_CreateWindow(title, x, y, w, h, flags | SDL_WINDOW_RESIZABLE );
    if (window) {
      std::cout << "Window created." << std::endl;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      // sets render scale info
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

  SDL_Rect tmpRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
  gameScreen = new GameObject("Resources/Assets/gameScreen.png",
                              tmpRect, 0, 0);
  
    
  map = new Map();
}

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

void Game::update() { // CHANGE TO MAP -> UPDATE
  map->update();
}

void Game::render() {
  SDL_RenderClear(renderer);
  
  gameScreen->render();

  // render stuff -- CHANGE TO MAP -> RENDER
  map->render();

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  IMG_Quit();
  
  std::cout << "Game cleaned." << std::endl;
}
