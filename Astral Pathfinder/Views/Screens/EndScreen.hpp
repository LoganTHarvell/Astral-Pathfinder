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
