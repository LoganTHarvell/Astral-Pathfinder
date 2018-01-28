//
//  main.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/14/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

// MARK: Source Files
#include "Game.hpp"

int main(int argc, const char * argv[]) {
  
  Game *game = new Game();
  game->init("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
             WINDOW_WIDTH, WINDOW_HEIGHT, false);
  
  Uint32 frameStart;
  int frameTime;
  
  while (game->running()) {
    // game loop
    frameStart = SDL_GetTicks();
    
    game->handleEvents();
    game->update();
    game->render();
    
    frameTime = SDL_GetTicks() - frameStart;
    
    if (FRAME_DELAY > frameTime) {
      SDL_Delay(FRAME_DELAY - frameTime);
    }
  }

  game->clean();

  return 0;
}
