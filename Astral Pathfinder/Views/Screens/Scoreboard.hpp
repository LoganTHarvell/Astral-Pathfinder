//
//  Scoreboard.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Extension of the Screen class for the Scoreboard screen. Initializes
//  appropriate UI elements and updates them accordingly.

#ifndef Scoreboard_hpp
#define Scoreboard_hpp

// MARK: Source Files
#include "Screen.hpp"


// MARK: - Scoreboard Class

class Scoreboard : public Screen {

public:
  
  // MARK: - Scoreboard Initialization
  
  void init();
  
  // MARK: - Game Loop Methods
  
  void update(Game::State *gs);
  void render(Game::State *gs);
  
  // MARK: - Scoreboard Methods
  
  void writeScore(Game::State *gs, int score);
  ID getNextScreen(int buttonID);
  
private:
  
  enum ButtonID {
    menu
  };
  
  // MARK: - Scoreboard Fields
  
  TextBox scoreList[20];
  int boardScores[10] = {-1};
  std::string names[10] = {""};
  
  // MARK: - Scoreboard Helper Methods
  
  void readScores();
  void compareScores(std::string name, int score);
};


#endif /* Scoreboard_hpp */
