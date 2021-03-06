//
//  main.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Entry point for the Astral Pathfinder application.
//  Simply loads parameters, creates and initializes an instance of the game,
//  and then maintains the main game loop at a minimum framerate.

// MARK: Source Files
#include "Parameters.hpp"
#include "Game.hpp"

int main(int argc, const char *argv[]) {
  using namespace Parameters::Game;
  
  Parameters::loadParameters();
  
  Game game;
  game.init("Astral Pathfinder ©", windowRect, false);

  // Tracks time to complete frame
  Uint32 frameStart = 0;
  Uint32 prevTick;
  int frameTime;
  
  // MARK: Game Loop
  while (game.running()) {
    prevTick = frameStart;
    frameStart = SDL_GetTicks();
    
    game.handleEvents();
    game.update(frameStart - prevTick);
    game.render();
    
    // Uses frame time and set frame delay to enforce FPS
    frameTime = SDL_GetTicks() - frameStart;
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }
  }

  game.clean();

  return 0;
}
