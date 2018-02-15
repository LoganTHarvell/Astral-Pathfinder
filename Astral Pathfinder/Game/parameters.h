//
//  parameters.h
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 11/20/15.
//  Copyright © 2015 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef parameters_h
#define parameters_h


/* TODO: - Move global defines to dependant files and remove this file. Mitigate
 global defines by converting them to class constants, private ones if possible.
 Make sure game parameters are easy to find and change. */


// MARK: Parameter Constants

//defines game introduction
#define TITLE "It is recommended you enlarge your screen for optimal gameplay.\n\
\n\
           =========================================================   \n\
           |             ___        __              __             |   \n\
           |            / _ |  ___ / /_ ____ ___ _ / /             |   \n\
           |           / __ | (_-</ __// __// _ `// /              |   \n\
           |          /_/ |_|/___/\\__//_/   \\_,_//_/               |   \n\
           |    ___         __   __    ___ _          __           |   \n\
           |   / _ \\ ___ _ / /_ / /   / _/(_)___  ___/ /___  ____  |   \n\
           |  / ___// _ `// __// _ \\ / _// // _ \\/ _  // -_)/ __/  |   \n\
           | /_/    \\_,_/ \\__//_//_//_/ /_//_//_/\\_,_/ \\__//_/     |   \n\
           |                                                   v1.0|   \n\
           ========================================================="

#define INTRO "Your homeworld is in trouble!\n\
The planet is no longer able to support a growing population.\n\
In order to let your society continue to grow, you have been chosen\n\
to manage your society's diminishing resources.\n\
It is up to you to colonize the planets of the galaxy, \n\
prepare for any unexpected disasters, and grow your population.\n\
\n\
You are the Astral Pathfinder."


// Defines planet information
#define NUMBER_OF_PLANETS 50

// Defines resource information
#define STARTING_POPULATION 5000
#define PEOPLE_FOOD_RQMT 50
#define FARMING_COST 25
#define MINING_COST 30
#define SHIP_COST 100
#define SHIP_PERSONNEL_RQMT 100
#define SHIP_FOOD_RQMT 4
#define INFRASTRUCTURE_COST 0.05

// Defines random event chances
#define ALIEN_ATTACK_CHANCE 0.005
#define BLIGHT_CHANCE 0.1
#define EXPLOSION_CHANCE 0.05
#define EPIDEMIC_CHANCE 0.05
#define EPIDEMIC_DEATH_RATE 0.8
#define SHIP_LOST_CHANCE 0.01

// Defines population growth information
#define MIN_BIRTH_MULTIPLIER 0.1
#define BIRTH_MULTIPLIER_RANGE (0.5-MIN_BIRTH_MULTIPLIER)
#define MIN_DEATH_MULTIPLIER 0.01
#define DEATH_MULTIPLIER_RANGE (0.1-MIN_DEATH_MULTIPLIER)

// Defines other info
#define RESOURCES 2
#define MAX_NUM_SCORES 10
#define MAX_NAME_LENGTH 20
#define MAX_NAME_LENGTH_STR "20" // MAX_NAME_LENGTH in string form
 
#endif /* parameters_h */
