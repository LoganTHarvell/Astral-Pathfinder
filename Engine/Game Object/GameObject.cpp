//
//  GameObject.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "GameObject.hpp"

// MARK: Libraries and Frameworks
#include <iostream>


// MARK: - GameObject Methods

ColliderComponent GameObject::getCollider() {
  return *collider;
}

SDL_Point GameObject::getPosition() {
  return { rect.x, rect.y };
}

void GameObject::setPosition(SDL_Point p) {
  rect.x = p.x;
  rect.y = p.y;
}

SDL_Rect GameObject::getRect() {
  return rect;
}

void GameObject::scale(float x) {
  rect.w *= x;
  rect.h *= x;
};

SDL_Point GameObject::getCenter() {
  SDL_Point c;
  c.x = rect.x + (rect.w/2);
  c.y = rect.y + (rect.h/2);
  return c;
}
