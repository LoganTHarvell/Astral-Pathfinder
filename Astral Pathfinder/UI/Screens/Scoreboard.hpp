//
//  Scoreboard.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Scoreboard_hpp
#define Scoreboard_hpp

#include "Screen.hpp"


// MARK: - Scoreboard Parameters
// TODO: - Move parameters to parameters file
namespace ScoreboardParameters {
  const std::string filePath = "Resources/Scores/scoreboard.txt";
  const int scoreboardMax = 10;
  const SDL_Rect startingNameBox = {760, 203, 300, 42};
  const SDL_Rect startingScoreBox = {880, 203, 300, 42};
  const SDL_Rect mainMenuButton = {628, 754, 376, 67};
  const SDL_Rect mainMenuBorder = {609, 742, 412, 90};
}


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
  
private:
  TextBox scoreList[20];
  int boardScores[10] = {-1};
  std::string names[10] = {""};
  
  void readScores();
  void compareScores(std::string name, int score);
};


#endif /* Scoreboard_hpp */
