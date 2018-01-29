//
//  Map.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 1/28/18.
//  Copyright © 2018 Ian Holdeman. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

// MARK: Source Files
#include "GameObject.hpp"
#include "parameters.h"
#include "Galaxy.hpp"

// MARK: Parameter Constants
#define GRID_OFFSET 50
#define GRID_X_ORIGIN MAP_X_ORIGIN + (GRID_OFFSET/2)
#define GRID_Y_ORIGIN MAP_Y_ORIGIN + (GRID_OFFSET/2)
#define GRID_WIDTH (MAP_WIDTH - GRID_OFFSET)/NUMBER_OF_PLANETS
#define GRID_HEIGHT (MAP_HEIGHT - GRID_OFFSET)/NUMBER_OF_PLANETS
#define PLANET_TEXTURE_SIZE 8
#define PLANET_TEXTURE_OFFSET_X (GRID_WIDTH - PLANET_TEXTURE_SIZE)/2
#define PLANET_TEXTURE_OFFSET_Y (GRID_HEIGHT - PLANET_TEXTURE_SIZE)/2

class GameObject;

class Map {
public:
    Map(Galaxy galaxy);
    ~Map();
    
    void update();
    void render();
    
private:
    static const SDL_Rect planetSrcRect;
    GameObject *ship;
    GameObject* planets[NUMBER_OF_PLANETS];
};

#endif /* Map_hpp */
