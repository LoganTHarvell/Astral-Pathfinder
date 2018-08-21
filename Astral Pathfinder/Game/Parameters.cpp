//
//  Parameters.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/2/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "LuaInterfaceSDL2.hpp"
#include <iostream>


// MARK: - Parameter Default Values

namespace Parameters {
  
  namespace Game {
    // Window parameters x, y, w, h
    SDL_Rect windowRect = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            1600, 900 };

    // FPS constants
    int fps = 60;                     // Number of frames per second
    int frameDelay = 1000/fps;        // Frame min length in ms (1000 ms/fps)

    int endgameDelay = 120;           // In number of frames
    int timeLimit = (20*60);          // In number of seconds (x min * 60 sec)
    int overtimeScaleFactor = 100;
  }
  
  namespace PlanetManager {
    int numberOfPlanets = 25;         // Number of planets in the game
  }

  namespace ShipManager {
    Uint32 alienTargetingDelay = 60;  // Alien ship seeking delay in frames
  }
  
  namespace UIManager {
    SDL_Rect screenRect = { 0, 0, Game::windowRect.w, Game::windowRect.h };
    SDL_Rect timeRect = { 115, 82, 90, 36 };
    SDL_Rect totalScoreRect = { 245, 82, 90, 36 };
    SDL_Rect shipInfoRect = { 1215, 100, 320, 121 };
    SDL_Rect currentPlanetRect = { 1215, 210, 320, 240 };
    SDL_Rect selectedPlanetRect = { 1215, 500, 320, 300 };
    SDL_Point endScoreCoords = { 945, 335 };
    SDL_Point endScoreName = { 940, 480 };
    SDL_Color red = { 128, 0, 0 };
    SDL_Color green = { 0, 128, 0 };
    SDL_Color yellow = { 255, 255, 0 };
  }
 
  namespace Planet {
    
    // Planet texture information
    std::string planetTextureFile = "../Resources/planet2.png";
    int planetTexSize = 16;
    
    std::string planetOutlineFile = "../Resources/planetOutline.png";
    int planetOutlineSize = 24;
    
    // Planet initial attribute information
    int minFertility = 20;
    int fertilityRange = (200 - minFertility);
    int minDeposits = 200;
    int depositsRange = (1000 - minDeposits);
    int startInfraPercent = 50;
    int startReservePercent = (100 - startInfraPercent);
    int startMiningPercent = 100;
    int startFarmingPercent = (100 - startMiningPercent);
    
    // Homeworld initial attribute values
    int homeStartPopulation = 5000;
    int homeStartFertility = 100;
    int homeStartDeposits = 250;
    int homeStartMiningPercent = 58;
    int homeStartFarmingPercent = (100 - homeStartMiningPercent);
    int homeStartInfraPercent = 0;
    int homeStartReservePercent = (100 - homeStartInfraPercent);
    
    // Defines population growth information
    int growthPeriod = 1200;          // Frames per growth period
    float starveRate = 0.0008;        // Starvation deaths per frame
    float minBirthMultiplier = 0.05;
    float birthMultiplierRange = (0.2 - minBirthMultiplier);
    float minDeathMultiplier = 0.025;
    float deathMultiplierRange = (0.075 - minDeathMultiplier);
    
    // Defines resource information
    float foodRqmt = 0.02;            // Food required per person
    float miningRate = 0.0001;        // Minerals produced per person per frame
    float farmingRate = 0.04;         // Food produced per person per frame
    float fertDecay = 0.0001;
    int fertDecayDelay = 10;          // Defined in seconds
    float infrastructureCost = 20;    // Max population increase per mineral
    
    // Random event chances in % chance per update
    float plagueRate = 0.05;
    float blightRate = 0.1;
    float mineCollapseRate = 0.3;
    float alienInvasionRate = 0.01;
    
    // Random event multipliers
    float plagueMultiplier = 1.33*(deathMultiplierRange+minDeathMultiplier);
    float blightMultiplier = 0.75;
    float mineCollapseMultiplier = 0.5;
  }
  
  namespace Ship {
    // Filename for player textures
    std::string movingPlayerTex = "../Resources/movingPlayerShip2.png";
    
    SDL_Rect shipRect = { 0, 0, 48, 24 };     // Ship Rect
    int totalCrew = 1000;                     // Ship Population
    
    // TODO: figure out real velocity/ticks formula
    int speed = 1;
    float alienSpeed = 0.5;
    int turnSpeed = 5;
  }
  
}


// MARK: - Parameter Loading Functions

// Loads Parameters from Lua config file
bool Parameters::loadParameters() {
  bool flag = true;
  
  LuaInterfaceSDL2 luaInterface = LuaInterfaceSDL2();
  
  flag = luaInterface.init(luaConfigFile);
  flag = luaInterface.loadTable(groups.gameParameters);
  
  if (flag) {
    Game::windowRect = luaInterface.getValueSDL<SDL_Rect>("windowRect");
    Game::fps = luaInterface.getValue<int>("fps");
  }
    
  return flag;
}
