//
//  GameObject.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

// MARK: Header File
#include "GameObject.hpp"

// MARK: Source Files
#include "Game.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* textureSheet, SDL_Rect srcRect,
                       int x, int y) {
  texture = TextureManager::loadTexture(textureSheet);
  
  srcR = srcRect;
  
  xpos = x;
  ypos = y;
  
  destR = srcR;
}

GameObject::~GameObject() {
  
}

void GameObject::update() {
  destR.x = xpos;
  destR.y = ypos;
}

void GameObject::render() {
  SDL_RenderCopy(Game::renderer, texture, &srcR, &destR);
}

void GameObject::scale(float x) {
  destR.w *= x;
  destR.h *= x;
}
