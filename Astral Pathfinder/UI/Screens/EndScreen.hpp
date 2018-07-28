//
//  EndScreen.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef EndScreen_hpp
#define EndScreen_hpp

#include "Screen.hpp"


namespace EndScreenParameters {
  const SDL_Rect playAgainButton = {288, 673, 424, 57};
  const SDL_Rect mainMenuButton = {885, 677, 424, 54};
  const SDL_Rect playAgainBorder = {270, 662, 460, 95};
  const SDL_Rect mainMenuBorder = {867, 666, 460, 92};
}

// MARK: - EndScreen Class

class EndScreen : public Screen {
public:
  // MARK: - EndScreen Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gs);
  void render(Game::State *gs);
};


#endif /* EndScreen_hpp */
