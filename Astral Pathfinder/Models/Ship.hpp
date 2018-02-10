//
//  Ship.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 2/10/18.
//  Copyright © 2018 Ian Holdeman. All rights reserved.
//

#ifndef Ship_hpp
#define Ship_hpp

#include <stdio.h>
#include "GameObject.hpp"

class Ship : public GameObject {
public:
    Ship(const char *textureSheet, SDL_Rect src, int x, int y);
    ~Ship();    
};

#endif /* Ship_hpp */
