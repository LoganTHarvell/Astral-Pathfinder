//
//  Game.cpp
//  SDL_Test
//
//  Created by Logan Harvell on 1/14/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#include "Game.hpp"

#include <iostream>

#include "Galaxy.hpp"
#include "GameObject.hpp"

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {
  
}

Game::~Game() {
  
}

void Game::init(const char * title, int x, int y, int w, int h, bool fullscreen) {
  
  int flags = 0;
  
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN;
  }
  
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "SDL initialised!..." << std::endl;
    
    window = SDL_CreateWindow(title, x, y, w, h, flags);

    if (window) {
      std::cout << "Window created." << std::endl;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      std::cout << "Renderer created." << std::endl;
    }
    
    isRunning = true;
    
  } else {
    isRunning = false;
  }
  
  galaxy = new Galaxy();
  
  SDL_Rect tmpRect = { 0, 0, 24, 32 };
  ship = new GameObject("Resources/Assets/simpleSpaceship.png",
                        tmpRect, MAP_X_ORIGIN, MAP_Y_ORIGIN);
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

void Game::update() {
  galaxy->update();
  ship->update();
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
  SDL_RenderClear(renderer);
  
  // Sets background
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_Rect rect = { MAP_X_ORIGIN, MAP_Y_ORIGIN, MAP_WIDTH, MAP_HEIGHT };
  SDL_RenderFillRect(renderer, &rect);
  rect = { INFO_X_ORIGIN, INFO_Y_ORIGIN, INFO_WIDTH, INFO_HEIGHT };
  SDL_RenderFillRect(renderer, &rect);
  rect = { INFO_X_ORIGIN, INFO2_Y_ORIGIN, INFO_WIDTH, INFO_HEIGHT };
  SDL_RenderFillRect(renderer, &rect);
  
  // render stuff
  galaxy->render();
  ship->render();

  SDL_RenderPresent(renderer);
}

void Game::clean() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();
  
  std::cout << "Game cleaned." << std::endl;
}
