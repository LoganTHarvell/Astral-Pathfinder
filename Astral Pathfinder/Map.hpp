//
//  Map.hpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 1/27/18.
//  Copyright © 2018 Ian Holdeman. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

// MARK: Source Files
#include "parameters.h"
#include "GameObject.hpp"

#define GRID_OFFSET 50
#define GRID_X_ORIGIN MAP_X_ORIGIN + (GRID_OFFSET/2)
#define GRID_Y_ORIGIN MAP_Y_ORIGIN + (GRID_OFFSET/2)
#define GRID_WIDTH (MAP_WIDTH - GRID_OFFSET)/NUMBER_OF_PLANETS
#define GRID_HEIGHT (MAP_HEIGHT - GRID_OFFSET)/NUMBER_OF_PLANETS
#define PLANET_TEXTURE_SIZE 8
#define PLANET_TEXTURE_OFFSET_X (GRID_WIDTH - PLANET_TEXTURE_SIZE)/2
#define PLANET_TEXTURE_OFFSET_Y (GRID_HEIGHT - PLANET_TEXTURE_SIZE)/2

class Map {
    struct Planet {
        enum Status {undiscovered, discovered, colonized};
        int xpos, ypos;
        int fertility;
        int deposits;
        Status status;
        GameObject *gameObject;
    };
    
public:
    Map();
    ~Map();
    
    Planet planets[NUMBER_OF_PLANETS];
    
    void update();
    void render();
    
private:
    static const SDL_Rect planetSrcRect;
    bool hasPlanet[NUMBER_OF_PLANETS][NUMBER_OF_PLANETS] = {false};
    GameObject *ship;
    
    void initShip();
    static Planet initHomeworld();
    static Planet initPlanet();
};


#endif /* Map_hpp */
