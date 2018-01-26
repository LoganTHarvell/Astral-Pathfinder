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

// MARK: Source Files
#include "Galaxy.hpp"
#include "GameObject.hpp"

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {
}

Game::~Game() {
}

void Game::init(const char * title,
                int x, int y, int w, int h, bool fullscreen) {
  
  int flags = 0;
  
  if (fullscreen) {
    flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
  }
  
  if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    std::cout << "SDL initialised!..." << std::endl;
    
    window = SDL_CreateWindow(title, x, y, w, h, flags | SDL_WINDOW_RESIZABLE );
    if (window) {
      std::cout << "Window created." << std::endl;
    }
    
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer) {
      // sets render scale info
      SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
      SDL_RenderSetLogicalSize(renderer, 1600, 900);
      
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      std::cout << "Renderer created." << std::endl;
    }
    
    isRunning = true;
    
  } else {
    isRunning = false;
  }

  SDL_Rect tmpRect = { 0, 0, 1600, 900 };
  gameScreen = new GameObject("Resources/Assets/gameScreen.png",
                              tmpRect, 0, 0);
  
  galaxy = new Galaxy();
  
  tmpRect = { 0, 0, 325, 628 };
  int xpos = galaxy->planets[0].gameObject->getPosition().x;
  int ypos = galaxy->planets[0].gameObject->getPosition().y;
  ship = new GameObject("Resources/Assets/simpleSpaceship.png",
                        tmpRect, xpos, ypos);
  ship->scale(0.07);
  ship->setPosition(xpos - (ship->getSize().w/2), ypos - (ship->getSize().h/2));
  
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
  SDL_RenderClear(renderer);
  
  gameScreen->render();

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
