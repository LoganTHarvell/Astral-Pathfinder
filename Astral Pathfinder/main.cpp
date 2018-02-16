//
//  main.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Source Files
#include "Game.hpp"


int main(int argc, const char *argv[]) {
  using namespace GameParameters;
  
  Game game;
  game.init("Astral Pathfinder ©", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            windowSize.w, windowSize.h, false);

  // Tracks time to complete frame
  Uint32 frameStart;
  int frameTime;
  
  // MARK: Game Loop
  while (game.running()) {

    frameStart = SDL_GetTicks();
    
    game.handleEvents();
    game.update();
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
