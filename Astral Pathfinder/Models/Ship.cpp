//
//  Ship.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/10/18.
//  Copyright © 2018 Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Ship.hpp"

// MARK: Source Files
#include "GameObject.hpp"
#include "TextureManager.hpp"

Ship::Ship(const char *textureSheet, SDL_Rect src, int x, int y) : GameObject(textureSheet, src, x, y) {
    // Invokes the parent's constructor, so nothing needs to be done for the time being
}

Ship::~Ship() {
    
}
