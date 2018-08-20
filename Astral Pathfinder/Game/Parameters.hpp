//
//  parameters.h
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/2/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef Parameters_hpp
#define Parameters_hpp


#include "SDL2/SDL.h"
#include <string>


// MARK: - Parameter Constants
namespace Parameters {
  
  const std::string title =
  "It is recommended you enlarge your screen for optimal gameplay.\n"
  R"(=========================================================)" "\n"
  R"(|             ___        __              __             |)" "\n"
  R"(|            / _ |  ___ / /_ ____ ___ _ / /             |)" "\n"
  R"(|           / __ | (_-</ __// __// _ `// /              |)" "\n"
  R"(|          /_/ |_|/___/\__//_/   \_,_//_/               |)" "\n"
  R"(|    ___         __   __    ___ _          __           |)" "\n"
  R"(|   / _ \ ___ _ / /_ / /   / _/(_)___  ___/ /___  ____  |)" "\n"
  R"(|  / ___// _ `// __// _ \ / _// // _ \/ _  // -_)/ __/  |)" "\n"
  R"(| /_/    \_,_/ \__//_//_//_/ /_//_//_/\_,_/ \__//_/     |)" "\n"
  R"(|                                                   v1.0|)" "\n"
  R"(=========================================================)";
  
  const std::string intro =
  "Your homeworld is in trouble!\n"
  "The planet is no longer able to support a growing population.\n"
  "In order to let your society continue to grow, you have been chosen\n"
  "to manage your society's diminishing resources.\n"
  "It is up to you to colonize the planets of the galaxy, \n"
  "prepare for any unexpected disasters, and grow your population.\n"
  "\n"
  "You are the Astral Pathfinder.";
  
  // Constants for parameter initialization
  namespace {
    const std::string luaConfigFile = "Resources/config.lua";
  
    struct {
      std::string gameParameters = "game";
      std::string planetManagerParameters = "planetManager";
      std::string shipManagerParameters = "shipManager";
      std::string uiManagerParameters = "uiManager";
      std::string planetParameters = "planet";
      std::string shipParameters = "ship";
    } groups;
  }
  
  // MARK: - Game Parameters
  namespace Game {
    // Window parameters x, y, w, h
    extern SDL_Rect windowRect;
    
    // FPS constants
    extern int fps;                     // Number of frames per second
    extern int frameDelay;              // Frame min length in ms (1000 ms/fps)
    
    extern int endgameDelay;            // In number of frames
    extern int timeLimit;               // In number of seconds (x min * 60 sec)
    extern int overtimeScaleFactor;
  }
  
  // MARK: - PlanetManager Parameters
  namespace PlanetManager {
    extern int numberOfPlanets;         // Number of planets in the game
  }
  
  // MARK: - ShipManager Parameters
  namespace ShipManager {
    extern Uint32 alienTargetingDelay;  // Alien ship seeking delay in frames
  }
  
  // MARK: - UIManager Parameters
  namespace UIManager {
    extern SDL_Rect screenRect;
    
    extern SDL_Rect timeRect;
    extern SDL_Rect totalScoreRect;
    extern SDL_Rect shipInfoRect;
    extern SDL_Rect currentPlanetRect;
    extern SDL_Rect selectedPlanetRect;
    
    extern SDL_Point endScoreCoords;
    extern SDL_Point endScoreName;
    
    extern SDL_Color red;
    extern SDL_Color green;
    extern SDL_Color yellow;
  }
  
  // MARK: - Planet Parameters
  namespace Planet {
    // Planet texture information
    extern std::string planetTextureFile;
    extern int planetTexSize;
    
    extern std::string planetOutlineFile;
    extern int planetOutlineSize;
    
    // Planet initial attribute information
    extern int minFertility;
    extern int fertilityRange;
    extern int minDeposits;
    extern int depositsRange;
    extern int startInfraPercent;
    extern int startReservePercent;
    extern int startMiningPercent;
    extern int startFarmingPercent;
    
    // Homeworld initial attribute values
    extern int homeStartPopulation;
    extern int homeStartFertility;
    extern int homeStartDeposits;
    extern int homeStartMiningPercent;
    extern int homeStartFarmingPercent;
    extern int homeStartInfraPercent;
    extern int homeStartReservePercent;
    
    // Defines population growth information
    extern int growthPeriod;          // Frames per growth period
    extern float starveRate;          // Starvation deaths per frame
    extern float minBirthMultiplier;
    extern float birthMultiplierRange;
    extern float minDeathMultiplier;
    extern float deathMultiplierRange;
    
    // Defines resource information
    extern float foodRqmt;            // Food required per person
    extern float miningRate;          // Minerals produced per person per frame
    extern float farmingRate;         // Food produced per person per frame
    extern float fertDecay;
    extern int fertDecayDelay;
    extern float infrastructureCost;  // Infrastructure per mineral
    
    // Random event chances
    extern float plagueRate;
    extern float blightRate;
    extern float mineCollapseRate;
    extern float alienInvasionRate;
    
    // Random event multipliers
    extern float plagueMultiplier;
    extern float blightMultiplier;
    extern float mineCollapseMultiplier;
  }
  
  // MARK: - Ship Parameters
  namespace Ship {
    // Ship Tags
    enum ShipType {
      playerShip,
      alienWarship
    };
    
    // Filename for player textures
    extern std::string movingPlayerTex;
    
    extern SDL_Rect shipRect;           // Ship Size
    extern int totalCrew;               // Ship Population
    
    // TODO: figure out real velocity/ticks formula
    extern int speed;
    extern float alienSpeed;
    extern int turnSpeed;
  }
  

  // MARK: - Parameter Loading Function
  bool loadParameters();
  
}


#endif /* parameters_h */
