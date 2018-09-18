//
//  GameObject.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Base class for creating a game object. Enabling the initialization,
//  update, and render of an entity to the screen with a bounding rectangle.
//  Also manages getters and setters for basic information about the object.

// MARK: Header File
#include "GameObject.hpp"

// MARK: Libraries and Frameworks
#include <iostream>


// MARK: - Initialization Methods

void GameObject::init(SDL_Rect rect, int rotation, SDL_Texture *texture) {
  this->rect = rect;
  this->rotation = rotation;
  this->texture = texture;
}


// MARK: - Game Loop Methods

void GameObject::update() {

}

void GameObject::render(SDL_Renderer *renderer) {
  SDL_RenderCopyEx(renderer, texture, NULL, &rect,
                   rotation, NULL, SDL_FLIP_NONE);
}


// MARK: - GameObject Methods

SDL_Point GameObject::getPosition() {
  return { rect.x, rect.y };
}

SDL_Rect GameObject::getRect() {
  return rect;
}

int GameObject::getRotation() {
  return rotation;
};

SDL_Point GameObject::getCenter() {
  SDL_Point c;
  c.x = rect.x + (rect.w/2);
  c.y = rect.y + (rect.h/2);
  return c;
}

ColliderComponent GameObject::getCollider() {
  return *collider;
}

void GameObject::setPosition(SDL_Point p) {
  rect.x = p.x;
  rect.y = p.y;
}

void GameObject::scale(float x) {
  rect.w *= x;
  rect.h *= x;
};
