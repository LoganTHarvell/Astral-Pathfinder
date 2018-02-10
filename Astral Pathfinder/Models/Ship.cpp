//
//  Ship.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/10/18.
//  Copyright © 2018 Ian Holdeman. All rights reserved.
//

#include "Ship.hpp"
#include "GameObject.hpp"
#include "TextureManager.hpp"

Ship::Ship(const char *textureSheet, SDL_Rect src, int x, int y) : GameObject(textureSheet, src, x, y) {
    
}

Ship::~Ship() {
    
}
