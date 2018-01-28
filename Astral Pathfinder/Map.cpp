//
//  Map.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 1/27/18.
//  Copyright © 2018 Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Map.hpp"

// MARK: Libraries and Frameworks
#include <stdlib.h>
#include <time.h>

// Mark: Source Files
#include "Game.hpp"

const SDL_Rect Map::planetSrcRect = {0, 0, PLANET_TEXTURE_SIZE, PLANET_TEXTURE_SIZE};

Map::Map() {
    srand((unsigned)time(NULL));
    
    int i = 0;
    planets[i] = initHomeworld();
    hasPlanet[planets[i].xpos][planets[i].ypos] = true;
    
    for(int i = 1; i < NUMBER_OF_PLANETS; i++) {
        planets[i] = initPlanet();
        hasPlanet[planets[i].xpos][planets[i].ypos] = true;
    }
    
    initShip();
};

Map::~Map() {
};

void Map::render() {
    for (int i = 0; i < NUMBER_OF_PLANETS; i++) {
        planets[i].gameObject->render();
    }
    
    ship -> render();
}

void Map::update() {
    for (int i = 0; i < NUMBER_OF_PLANETS; i++) {
        planets[i].gameObject->update();
    }
    
    ship -> update();
}

Map::Planet Map::initHomeworld() {
    Planet homeworld;
    
    // Sets homeworld coordinates
    homeworld.xpos = rand()%NUMBER_OF_PLANETS;
    homeworld.ypos = rand()%NUMBER_OF_PLANETS;
    
    // Sets homeworld resources
    homeworld.fertility = STARTING_POPULATION/PEOPLE_FOOD_RQMT;
    homeworld.deposits = SHIP_COST * 2 + 50;
    
    // Initializes homeworld max population to starting population
    homeworld.status = Planet::colonized;
    
    // Initializes game object
    int x = GRID_X_ORIGIN + (homeworld.xpos * GRID_WIDTH) + PLANET_TEXTURE_OFFSET_X;
    int y = GRID_Y_ORIGIN + (homeworld.ypos * GRID_HEIGHT) + PLANET_TEXTURE_OFFSET_Y;
    homeworld.gameObject = new GameObject("Resources/Assets/planet.png", planetSrcRect, x, y);
    
    return homeworld;
}

Map::Planet Map::initPlanet() {
    Planet planet;
    
    // Set planet coordinates
    planet.xpos = rand()%NUMBER_OF_PLANETS;
    planet.ypos = rand()%NUMBER_OF_PLANETS;
    
    // Sets planet fertility to random value
    planet.fertility = (rand()%(MAX_FERTILITY-MIN_FERTILITY+1) + MIN_FERTILITY);
    
    // Sets planet deposits to random value
    planet.deposits = (rand()%(DEPOSITS_RANGE+1)) + MIN_DEPOSITS;
    
    // Initializes max population to 0
    planet.status = Planet::undiscovered;
    
    // Initializes game object
    int x = GRID_X_ORIGIN + (planet.xpos * GRID_WIDTH) + PLANET_TEXTURE_OFFSET_X;
    int y = GRID_Y_ORIGIN + (planet.ypos * GRID_HEIGHT) + PLANET_TEXTURE_OFFSET_Y;
    planet.gameObject = new GameObject("Resources/Assets/planet.png", planetSrcRect, x, y);
    
    return planet;
}

void Map::initShip() {
    SDL_Rect tmpRect = { 0, 0, 24, 45 };
    int xpos = planets[0].gameObject->getPosition().x;
    int ypos = planets[0].gameObject->getPosition().y;
    ship = new GameObject("Resources/Assets/simpleSpaceship.png", tmpRect, xpos, ypos);
    ship->setPosition(xpos - (ship->getSize().w/2), ypos - (ship->getSize().h/2));
}
