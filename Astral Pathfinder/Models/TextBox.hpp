//
//  TextBox.hpp
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

// MARK: - TextBox Parameters

namespace TextParameters {
  const SDL_Color color = {255, 255, 255};
}


class TextBox : public GameObject {
public:
  // MARK: - Initialization Methods
  void init(SDL_Rect rect);
  
  // MARK: - Game Loop Methods
  void update();
  void render();
  
  void setMessage(const char *words);
  void reset();
  
  
private:
  TTF_Font *font;
  SDL_Surface *surface;
};

#endif /* Text_hpp */
