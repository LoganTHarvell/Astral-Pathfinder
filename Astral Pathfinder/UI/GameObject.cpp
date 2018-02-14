//
//  GameObject.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "GameObject.hpp"

// MARK: Source Files
#include "Game.hpp"
#include "TextureManager.hpp"


// MARK: - GameObject Functions

void GameObject::update() {
  
  // Updates destination rect position and size
  destR.x = position.x;
  destR.y = position.y;
  destR.w = size.w;
  destR.h = size.h;
  
}

void GameObject::render() {
  
  // Renders game object in destination rect
  SDL_RenderCopy(Game::renderer, texture, &srcR, &destR);
  
}

