//
//  Parameters.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/2/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Namespace containing all game parameters. Organized into
//  groups by class. Function declared for parameter loading from file.

#ifndef Parameters_hpp
#define Parameters_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include <string>


// MARK: - Parameter Constants
// TODO: Make a Singleton class
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
  
  namespace {
    // Base file path for resources directory
    const std::string resourcePath = SDL_GetBasePath();
    
    const std::string luaConfigFile = resourcePath + "config.lua";
  
    struct {
      std::string gameParameters = "game";
      std::string planetManagerParameters = "planetManager";
      std::string shipManagerParameters = "shipManager";
      std::string uiManagerParameters = "uiManager";
      std::string planetParameters = "planet";
      std::string shipParameters = "ship";
      std::string uiParameters = "ui";
    } tables;
  }
  
  // MARK: - Game Parameters
  
  namespace Game {
    // Window parameters x, y, w, h
    extern SDL_Rect windowRect;
    
    // FPS constants
    extern int fps;
    extern int frameDelay;
    
    // Delay before game exits to endgame screen
    extern int endgameDelay;
    
    // Time limit info
    extern int timeLimit;
    extern int timeLimitWarning;
    
    // Multiplier for decreasing score during overtime
    extern int overtimeFactor;
  }
  
  // MARK: - PlanetManager Parameters
  
  namespace PlanetManager {
    extern int numberOfPlanets;
  }
  
  // MARK: - ShipManager Parameters
  
  namespace ShipManager {
    // Delay before alien warship selects a new target
    extern Uint32 alienTargetingDelay;
  }
  
  // MARK: - UIManager Parameters
  
  namespace UIManager {
    // Main screen rect geometry in { x, y, w, h }
    extern SDL_Rect screenRect;
    
    // UI element rect geometry in { x, y, w, h }
    extern SDL_Rect timeRect;
    extern SDL_Rect totalScoreRect;
    extern SDL_Rect shipInfoRect;
    extern SDL_Rect currentPlanetRect;
    extern SDL_Rect selectedPlanetRect;
    
    //  Score and name scoreboard position in { x, y }
    extern SDL_Point endScoreCoords;
    extern SDL_Point endNameCoords;
    
    // Color values for UI color coding
    extern SDL_Color badColor;
    extern SDL_Color goodColor;
    extern SDL_Color warningColor;
    
    // File path to main game screen background texture
    extern std::string gameScreenFile;
  }
  
  // MARK: - Planet Parameters
  
  namespace Planet {
    // Planet texture information
    extern std::string planetTextureFile;
    extern int planetTexSize;
    extern std::string planetOutlineFile;
    extern int planetOutlineSize;
    
    extern Uint8 normalAlpha;
    extern SDL_Color undiscColor;
    extern SDL_Color discoverColor;
    extern SDL_Color colonyColor;
    extern SDL_Color popDecColor;
    extern SDL_Color overprodColor;
    extern SDL_Color selectedColor;
    
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
    
    // Population growth information
    extern int growthPeriod;
    extern float starveRate;
    extern float minBirthMultiplier;
    extern float birthMultiplierRange;
    extern float minDeathMultiplier;
    extern float deathMultiplierRange;
    
    // Resource information
    extern float foodRqmt;
    extern float miningRate;
    extern float farmingRate;
    extern float fertDecay;
    extern int fertDecayDelay;
    extern float infrastructureCost;
    
    // Random event chances in % chance per event cycle or event
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
    extern std::string playerTexFile;
    extern std::string alienTexFile;

    // Ship rect geometry in { x, y, w, h }
    extern SDL_Rect shipRect;
    extern int shipPopulation;
    
    // Ship speeds
    extern int speed;
    extern float alienSpeed;
    extern int turnSpeed;
  }
  
  // MARK: - UI Parameters
  
  namespace UI {
    // Map Parameters
    
    namespace Map {
      extern SDL_Rect rect;
      extern int gridOffset;
    }
    
    // Events Panel Parameters
    
    namespace EventPanel {
      // UI element rect geometry in { x, y, w, h }
      extern SDL_Rect panelRect;
      extern SDL_Rect renderRect;
      extern SDL_Rect textBoxesRect;
      
      // Event color coding in { r, g, b } (0-255)
      extern SDL_Color overprodColor;
      extern SDL_Color popDeclineColor;
      extern SDL_Color outlineColor;
    }
    
    // Main Menu Parameters
    
    namespace MainMenu {
      extern std::string textureFile;
      
      extern SDL_Rect startGameButton;
      extern SDL_Rect scoreboardButton;
      extern SDL_Rect exitGameButton;
      
      extern SDL_Rect startGameBorder;
      extern SDL_Rect scoreboardBorder;
      extern SDL_Rect exitGameBorder;
    }
    
    // Scoreboard Parameters
    
    namespace Scoreboard {
      extern std::string textureFile;
      extern std::string scoresFile;
      
      extern int scoreboardMax;
      
      extern SDL_Rect startingNameBox;
      extern SDL_Rect startingScoreBox;
      
      extern SDL_Rect mainMenuButton;
      extern SDL_Rect mainMenuBorder;
    }
    
    // End Screen Parameters
    
    namespace EndScreen {
      extern SDL_Rect playAgainButton;
      extern SDL_Rect mainMenuButton;
      
      extern SDL_Rect playAgainBorder;
      extern SDL_Rect mainMenuBorder;
      
      extern std::string winTextureFile;
      extern std::string loseTextureFile;
      extern std::string crashTextureFile;
    }
    
    // TextBox Parameters
    
    namespace TextBox {
      extern SDL_Color color;
      extern std::string fontFile;
      
      extern int regFontSize;
      extern int eventFontSize;
      extern int finalScoreFontSize;
      
      extern Uint32 wrapLength;
      extern int scoreboardLine;
    }
    
    // Slider Parameters
    
    namespace Slider {
      extern std::string baseTexFile;
      extern std::string sliderTexFile;
      
      extern SDL_Color baseColor;
      extern SDL_Color sliderColor;
    }
    
    // Button Parameters
    
    namespace Button {
      extern std::string textureFile;
    }
  }

  // MARK: - Parameter Loading Functions
  
  bool loadParameters();
  
}


#endif /* parameters_h */
