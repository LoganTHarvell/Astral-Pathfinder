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

GameObject::GameObject(const char* textureSheet,
                       SDL_Rect srcRect, int x, int y) {
  texture = TextureManager::loadTexture(textureSheet);
  
  srcR = srcRect;
  
  destR.x = position.x = x;
  destR.y = position.y = y;
  destR.w = size.w = srcR.w;
  destR.h = size.h = srcR.h;
}

GameObject::~GameObject() {
  
}

void GameObject::update() {
  destR.x = position.x;
  destR.y = position.y;
  destR.w = size.w;
  destR.h = size.h;
}

void GameObject::render() {
  SDL_RenderCopy(Game::renderer, texture, &srcR, &destR);
}

void GameObject::setPosition(int x, int y) {
  position.x = x;
  position.y = y;
}

GameObject::Coordinates GameObject::getPosition() {
  return position;
}

GameObject::Size GameObject::getSize() {
  return size;
}

void GameObject::scale(float x) {
  size.w *= x;
  size.h *= x;
}
