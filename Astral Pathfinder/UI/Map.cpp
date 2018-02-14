//
//  Map.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/28/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Map.hpp"

// MARK: Source Files



SDL_Point Map::uiPosition(SDL_Point position) {
  
  int x = GRID_X_ORIGIN + (position.x * GRID_WIDTH) + PLANET_TEXTURE_OFFSET_X;
  int y = GRID_Y_ORIGIN + (position.y * GRID_HEIGHT) + PLANET_TEXTURE_OFFSET_Y;
  
  return { x, y };
}

//void Map::loadShip() {
//  // Initialize Ship
//  SDL_Rect tmpRect = { 0, 0, 24, 45 };
//
//  int xpos = planets[0] -> getPosition().x;
//  int ypos = planets[0] -> getPosition().y;
//  ship = new GameObject("Resources/Assets/simpleSpaceship.png",
//                        tmpRect, xpos, ypos);
//  ship->setPosition(xpos - (ship->getSize().w/2), ypos - (ship->getSize().h/2));
//}

//void Map::update() {
//  // Updates planet game objects
//  for (int i = 0; i < NUMBER_OF_PLANETS; i++)
//      planets[i]->update();
//  
//  // Updates the ship game object
//  ship->update();
//}
//
//void Map::render() {
//  // Renders the planet game objects
//  for (int i = 0; i < NUMBER_OF_PLANETS; i++)
//      planets[i]->render();
//  
//  // Renders the ship game object
//  ship->render();
//}

