//
//  Scoreboard.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "Scoreboard.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

void Scoreboard::init() {
  using namespace ScoreboardParameters;
  
  texture = TextureManager::loadTexture("../Resources/scoreboard.png");
  
  TextBox box;
  SDL_Rect temp;
  for(int i = 0; i < scoreboardMax; i++) {
    scoreList[i*2] = box;
    scoreList[i*2+1] = box;
    temp = {startingNameBox.x, startingNameBox.y+(53*i),
      startingNameBox.w, startingNameBox.h};
    scoreList[i*2].init(temp);
    temp = {startingScoreBox.x, startingScoreBox.y+(53*i),
      startingScoreBox.w, startingScoreBox.h};
    scoreList[(i*2)+1].init(temp);
  }
  readScores();
}

void Scoreboard::update(Game::State *gs) {
  
}

void Scoreboard::render(Game::State *gs) {
  using namespace ScoreboardParameters;
  
  SDL_RenderCopy(Game::renderer, texture, NULL, &ScreenParameters::screenRect);
  
  if(borderRect.y != 0)
    SDL_RenderCopy(Game::renderer, hoveringBorder, NULL, &borderRect);
  
  for(int i = 0; i < scoreboardMax; i++) {
    if(scores[i] > -1) {
      scoreList[i*2].render(gs);
      scoreList[(i*2)+1].render(gs);
    }
  }
}

void Scoreboard::checkForHovering(Game::State *gs) {
  using namespace ScoreboardParameters;
  SDL_Point p = gs->dragLocation;
  
  if((p.x > mainMenuButton.x) && (p.x < mainMenuButton.x + mainMenuButton.w)
     && (p.y > mainMenuButton.y) && (p.y < mainMenuButton.y + mainMenuButton.h))
      borderRect = mainMenuBorder;

  else borderRect = {};
}

int Scoreboard::checkClick(Game::State *gs) {
  using namespace ScoreboardParameters;
  SDL_Point p = gs->clickLocation;
  borderRect = {};
  
  if((p.x > mainMenuButton.x) && (p.x < mainMenuButton.x + mainMenuButton.w)
     && (p.y > mainMenuButton.y) && (p.y < mainMenuButton.y + mainMenuButton.h))
    return activeScreen::menu;
  
  else return activeScreen::none;
}

void Scoreboard::writeScore(Game::State *gs, int score) {
  using namespace std;
  ofstream file;
  file.open(ScoreboardParameters::filePath.c_str(), ios::app);
  while(gs->playerName.length() < 3)
    gs->playerName += '-';
  string message = gs->playerName + ";" + to_string(score) + ";";
  file << message << endl;
  file.close();
}

void Scoreboard::readScores() {
  using namespace std;
  
  const char lineBreak = ';';
  string line;
  ifstream file;
  file.open(ScoreboardParameters::filePath.c_str());
  while(static_cast<void>(file >> ws), getline(file, line, lineBreak)) {
    // Player Name
    string name = line;
    // Player Score
    getline(file, line, lineBreak);
    stringstream s(line);
    int score;
    s >> score;
    
    compareScores(name, score);
  }
  
  file.close();
}

void Scoreboard::compareScores(std::string name, int score) {
  int tempScore;
  std::string tempName;
  TextBox tempBox;
  
  for(int i = 0; i < ScoreboardParameters::scoreboardMax; i++) {
    if (score > scores[i]) {
      tempScore = scores[i];
      scores[i] = score;
      score = tempScore;
      
      tempName = names[i];
      names[i] = name;
      name = tempName;
      
      scoreList[i*2].setScoreboardMessage(names[i] + ": ");
      scoreList[(i*2)+1].setScoreboardMessage(std::to_string(scores[i]).c_str());
    }
  }
}
