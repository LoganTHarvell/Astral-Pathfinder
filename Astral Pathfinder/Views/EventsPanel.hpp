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
#include <vector>
#include <unordered_map>

// MARK: Source Files
#include "Game.hpp"
#include "TextBox.hpp"
#include "EventsComponent.hpp"
#include "PlanetManager.hpp"


// MARK: - Events Panel Class

class EventsPanel {
public:
  // MARK: - EventsPanel Initialization
  void init();
  
  // MARK: - Game Loop Methods
  void update(Game::State *gameState, PlanetManager *pm);
  void render(Game::State *gameState);
  
private:
  // MARK: - EventsPanel Fields
  enum {
    BLIGHT=1, PLAGUE, MINECOLLAPSE, POPDEC, OVERPROD, TEST
  };
  
  SDL_Texture *texture = nullptr;
  std::unordered_map<long, TextBox> map;
  std::vector<TextBox> eventOrder;
  SDL_Rect src;
  int totalHeight;
  
  // MARK: - Helper Methods
  void scrollPanel(int scroll);
  void checkStatus(std::vector<EventsComponent> events);
  void updateMap(SDL_Point p, bool flag, int event, SDL_Color color);
  void removeFromList(long key);
  std::string createMessage(SDL_Point p, int event);
  void updateBoxCoords();
};

#endif /* EventsPanel_hpp */
