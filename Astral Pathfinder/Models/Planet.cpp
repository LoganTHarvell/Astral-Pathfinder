//
//  Planet.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 2/10/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Planet.hpp"

Planet::Planet() {
  
}

Planet::~Planet() {
  
}

void Planet::initHomeworld() {
  // Set planet coordinates
  this->position.x = rand()%NUMBER_OF_PLANETS;
  this->position.y = rand()%NUMBER_OF_PLANETS;
  
  // Sets homeword resources
  this->fertility = STARTING_POPULATION/PEOPLE_FOOD_RQMT;
  this->deposits = SHIP_COST * 2 + 50;
  
  // Sets homeworld status
  this->status = colonized;
}

void Planet::initPlanet() {
  // Set planet coordinates
  this->position.x = rand()%NUMBER_OF_PLANETS;
  this->position.y = rand()%NUMBER_OF_PLANETS;
  
  // Sets planet fertility to random value
  this->fertility = (rand()%(MAX_FERTILITY-MIN_FERTILITY+1) + MIN_FERTILITY);
  
  // Sets planet deposits to random value
  this->deposits = (rand()%(DEPOSITS_RANGE+1)) + MIN_DEPOSITS;
  
  // Sets planet status
  this->status = undiscovered;
}

int Planet::getPositionX() {
  return this->position.x;
}

int Planet::getPositionY() {
  return this->position.y;
}

int Planet::getDeposits() {
  return this->deposits;
}

int Planet::getFertility() {
  return this->fertility;
}
