//
//  Screen.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Abstract base class for all screens containing essential properties and
//  methods for managing UI elements, and handling some events. Also contains
//  virtual methods to ensure implementation of required game loop methods.

#ifndef Screen_hpp
#define Screen_hpp


// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include <vector>
#include <map>

// MARK: Source Files
#include "TextBox.hpp"
#include "Game.hpp"
#include "TextureManager.hpp"
#include "Button.hpp"


// MARK: - Screen Class
// TODO: Make a generic class without game specific attributes

class Screen {
  
public:
  // Screen Identifiers
  enum ID {
    none=-1, menu, scores, game, over, quit
  };
  
  // MARK: - Screen Initialization
  virtual void init() = 0;
  
  // MARK: - Game Loop Methods
  virtual void update(Game::State *gs) = 0;
  virtual void render(Game::State *gs) = 0;
  
  // MARK: - Screen Methods
  void checkForHovering(Game::State *gs);
  int checkClick(Game::State *gs);
  
  // TODO: Rework buttons without screen information, make buttons generic
  void addButton(int id, SDL_Rect bounds, SDL_Rect border);
  void renderButtons();
  
protected:
  
  // MARK: - Screen Fields

  SDL_Texture *texture = nullptr;
  SDL_Rect borderRect;
    
private:
  
  std::vector<Button> buttons;
  std::map<int, int> actions;
  
};

#endif /* Screen_hpp */
