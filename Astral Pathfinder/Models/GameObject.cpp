//
//  GameObject.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "GameObject.hpp"

// MARK: - GameObject Methods

SDL_Point GameObject::getPosition() {
  return position;
}

void GameObject::setPosition(int x, int y) {
  position.x = x; position.y = y;
}

GameObject::Size GameObject::getSize() {
  return size;
}

void GameObject::scale(float x) {
  size.w *= x; size.h *= x;
};

