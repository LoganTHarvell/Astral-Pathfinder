//
//  Text.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/24/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Text_hpp
#define Text_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include "Game.hpp"

// MARK: Source Files
#include "GameObject.hpp"

// MARK: - Ship Parameters

namespace TextParameters {
  const SDL_Color color = {255, 255, 255};
}


class Text : public GameObject {
public:
  // MARK: - Initialization Methods
  void initDeposits();
  void initFertility();
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  
  void setMessage(const char *words);
  void reset();
  
  
private:
  SDL_Surface *surface;
  TTF_Font *font;
  char *message;
};

#endif /* Text_hpp */
