//
//  EventsPanel.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 4/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef EventsPanel_hpp
#define EventsPanel_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

// MARK: Source Files
#include "TextBox.hpp"
#include "Game.hpp"


// MARK: - TextBox Parameters

namespace EventPanelParameters {

}


class EventsPanel {
public:
  // MARK: - EventsPanel Initialization
  void init(SDL_Rect src);
  
  // MARK: - Game Loop Methods
  void update();
  void render(Game::State *gameState);
  void clean();
  
private:
  SDL_Rect rect = {320, 320, 350, 500};
  SDL_Texture *texture;
  TextBox sample, sample2, sample3, sample4, sample5;
};

#endif /* EventsPanel_hpp */
