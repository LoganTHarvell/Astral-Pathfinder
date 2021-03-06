//
//  MainMenu.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Extension of the Screen class for the Main Menu screen. Initializes
//  appropriate UI elements and updates them accordingly.

#ifndef MainMenu_hpp
#define MainMenu_hpp

// MARK: Source Files
#include "Screen.hpp"

// MARK: - MainMenu Class

class MainMenu : public Screen {

public:
  
  // MARK: - MainMenu Initialization
 
  void init();
  
  // MARK: - Game Loop Methods
  
  void update(Game::State *gs);
  void render(Game::State *gs);
  
  // MARK: - MainMenu Methods
  
  ID getNextScreen(int buttonID);
  
private:
  
  // Button identifiers
  enum ButtonID {
    play, scores, quit
  };

};

#endif /* MainMenu_hpp */
