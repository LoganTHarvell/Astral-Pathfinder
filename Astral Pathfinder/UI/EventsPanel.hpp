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
#include "EventsComponent.hpp"
#include "PlanetManager.hpp"

#include <vector>
#include <map>


// MARK: - TextBox Parameters

namespace EventPanelParameters {
  const SDL_Rect panelRect = {65, 175, 320, 7000};
  const SDL_Rect renderRect = {70, 180, 310, 590};
  const SDL_Rect textBoxesRect = {0,0,300,0};
  const SDL_Color red = {200, 0, 0};
  const SDL_Color yellow = {200, 200, 0};
  const SDL_Color outline = {177, 115, 6};
}


class EventsPanel {
public:
  // MARK: - EventsPanel Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *pm);
  void render(Game::State *gameState);
  
private:
  enum {
    BLIGHT=1, PLAGUE, MINECOLLAPSE, POPDEC, OVERPROD, TEST
  };
  
  SDL_Texture *texture;
  TextBox sample, sample2, sample3, sample4, sample5;
  std::map<long, TextBox> map;
  bool changedFlag;
  SDL_Rect src;
  int totalHeight;
  
  void scrollPanel(int scroll);
  void checkStatus(std::vector<EventsComponent> events);
  void updateMap(SDL_Point p, bool flag, int event, SDL_Color color);
  std::string createMessage(SDL_Point p, int event);
  void updateBoxCoords();
};

#endif /* EventsPanel_hpp */
