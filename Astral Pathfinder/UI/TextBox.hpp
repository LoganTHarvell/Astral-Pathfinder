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
#include "SDL2_ttf/SDL_ttf.h"
#include <string>

// MARK: Source Files
#include "Game.hpp"
#include "GameObject.hpp"


// MARK: - TextBox Parameters

namespace TextParameters {
  const SDL_Color color = {0,128,0};
  const std::string fontFile = "../Resources/MODENINE.TTF";
}


// MARK: - TextBox Class

class TextBox : public GameObject {
public:
  // MARK: - Initialization Methods
  void init(SDL_Rect rect);
  
  // MARK: - Game Loop Methods
  void update(Game::State *gs);
  void render(Game::State *gs);
  void clean();
  
  // MARK: - TextBox Methods
  void setMessage(const std::string words, SDL_Color color = TextParameters::color);
  void setFinalScore(TTF_Font *newFont, const std::string words);
  bool checkNull();
  void setRect(int x, int w);
  
  
private:
  // MARK: - Textbox Fields
  TTF_Font *font;
};

#endif /* Text_hpp */
