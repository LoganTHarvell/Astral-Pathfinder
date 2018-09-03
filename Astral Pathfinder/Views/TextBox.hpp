//
//  TextBox.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/24/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef TextBox_hpp
#define TextBox_hpp

// MARK: Parameter File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <string>

// MARK: Source Files
#include "Game.hpp"
#include "GameObject.hpp"


// MARK: - TextBox Class
// TODO: - Needs reworking as a general use class and moved into Engine

class TextBox : public GameObject {
public:
  // MARK: - Initialization Methods
  void init(SDL_Rect rect);
  
  // MARK: - Game Loop Methods
  void update(Game::State *gs);
  void render(Game::State *gs);
  void clean();
  
  // MARK: - TextBox Methods
  void setMessage(const std::string words, SDL_Color color = Parameters::UI::TextBox::color);
  void setFuelMessage(const std::string words, SDL_Color color = Parameters::UI::TextBox::color);
  void setScoreboardMessage(const std::string words, SDL_Color color = Parameters::UI::TextBox::color);
  void setEventMessage(const std::string words, SDL_Color color);
  void setFinalScore(const std::string words);
  bool checkNull();
  void setRect(int x, int w);
  SDL_Rect getRect() { return rect; }
  void setYCoord(int y) { rect.y = y; }
  void setKey(long k) { key = k; }
  long getKey() { return key; }
  
  
private:
  // MARK: - Textbox Fields
  TTF_Font *font;
  long key;
};

#endif /* TextBox_hpp */
