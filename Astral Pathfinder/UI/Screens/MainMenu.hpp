//
//  MainMenu.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 7/14/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include "Screen.hpp"

// TODO: - Move parameters to parameters file
namespace MainMenuParameters {
  const SDL_Rect startGameButton = {600, 401, 424, 57};
  const SDL_Rect scoreboardButton = {600, 538, 424, 58};
  const SDL_Rect exitGameButton = {600, 676, 424, 54};
  const SDL_Rect startGameBorder = {582, 390, 460, 95};
  const SDL_Rect scoreboardBorder = {582, 527, 460, 96};
  const SDL_Rect exitGameBorder = {582, 665, 460, 92};
}

// MARK: - MainMenu Class

class MainMenu : public Screen {
public:
  // MARK: - MainMenu Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gs);
  void render(Game::State *gs);
};

#endif /* MainMenu_hpp */
