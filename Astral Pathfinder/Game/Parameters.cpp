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
    int overtimeFactor = 100;
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
    SDL_Point endNameCoords = { 940, 480 };
    
    SDL_Color badColor = { 128, 0, 0 };
    SDL_Color goodColor = { 0, 128, 0 };
    SDL_Color warningColor = { 255, 255, 0 };
    
    std::string gameScreenFile = "../Resources/gameScreen2.png";

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
    std::string playerTexFile = "../Resources/movingPlayerShip2.png";
    std::string alienTexFile = "../Resources/alienShip.png";
    
    SDL_Rect shipRect = { 0, 0, 48, 24 };     // Ship Rect
    int totalCrew = 1000;                     // Ship Population
    
    int speed = 1;
    float alienSpeed = 0.5;
    int turnSpeed = 5;
  }
  
  namespace UI {
    namespace EventPanel {
      SDL_Rect panelRect = { 65, 175, 320, 10000 };
      SDL_Rect renderRect = { 70, 180, 310, 590 };
      SDL_Rect textBoxesRect = { 0, 0, 300, 0 };
      
      SDL_Color overprodColor = { 200, 0, 0 };
      SDL_Color popDeclineColor = { 200, 200, 0 };
      SDL_Color outlineColor = { 177, 115, 6 };
    }
    
    namespace MainMenu {
      std::string textureFile = "../Resources/mainMenu.png";
      
      SDL_Rect startGameButton = { 600, 401, 424, 57 };
      SDL_Rect scoreboardButton = { 600, 538, 424, 58 };
      SDL_Rect exitGameButton = { 600, 676, 424, 54 };
      
      SDL_Rect startGameBorder = { 582, 390, 460, 95 };
      SDL_Rect scoreboardBorder = { 582, 527, 460, 96 };
      SDL_Rect exitGameBorder = { 582, 665, 460, 92 };
    }
    
    namespace Scoreboard {
      std::string textureFile = "../Resources/scoreboard.png";
      std::string scoresFile = "Resources/Scores/scoreboard.txt";
      
      int scoreboardMax = 10;
      
      SDL_Rect startingNameBox = { 760, 203, 300, 42 };
      SDL_Rect startingScoreBox = { 880, 203, 300, 42 };
      
      SDL_Rect mainMenuButton = { 628, 754, 376, 67 };
      SDL_Rect mainMenuBorder = { 609, 742, 412, 90 };
    }
    
    namespace EndScreen {
      SDL_Rect playAgainButton = { 288, 673, 424, 57 };
      SDL_Rect mainMenuButton = { 885, 677, 424, 54 };
      
      SDL_Rect playAgainBorder = { 270, 662, 460, 95 };
      SDL_Rect mainMenuBorder = { 867, 666, 460, 92 };
      
      std::string winTextureFile = "../Resources/winScreen.png";
      std::string loseTextureFile = "../Resources/loseScreen.png";
      std::string crashTextureFile = "../Resources/alienScreen.png";
    }
    
    namespace TextBox {
      SDL_Color color = { 0, 128, 0 };
      std::string fontFile = "../Resources/MODENINE.TTF";
      
      int regFontSize = 36;
      int eventFontSize = 18;
      int finalScoreFontSize = 120;
      
      Uint32 wrapLength = 300;
      int scoreboardLine = 880;
    }
  
    namespace Slider {
      std::string baseFilename = "../Resources/base.png";
      std::string knobFilename = "../Resources/slider.png";
      
      SDL_Color baseColor = { 150, 150, 150 };
      SDL_Color knobColor = { 0, 128, 0 };
    }
    
    namespace Button {
      std::string textureFile = "../Resources/border.png";
    }
      
  }
  
}


// MARK: - Parameter Loading Functions

// Loads Parameters from Lua config file
bool Parameters::loadParameters() {
  LuaInterfaceSDL2 luaInterface = LuaInterfaceSDL2();
  
  // Initializes Lua config file
  if (!luaInterface.init(luaConfigFile)) return false;
  
  // Loads and reads Game table
  if (luaInterface.loadTable(tables.gameParameters)) {
    using namespace Game;
    
    windowRect = luaInterface.getValueSDL<SDL_Rect>("windowRect");
    fps = luaInterface.getValue<int>("fps");
    frameDelay = 1000 / Game::fps;
    endgameDelay = luaInterface.getValue<int>("endgameDelay");
    timeLimit = luaInterface.getValue<int>("timeLimit");
    overtimeFactor = luaInterface.getValue<int>("overtimeFactor");
    
    luaInterface.unloadTable();
  }

  // Loads and reads PlanetManager table
  if (luaInterface.loadTable(tables.planetManagerParameters)) {
    using namespace PlanetManager;
    
    numberOfPlanets = luaInterface.getValue<int>("numberOfPlanets");
 
    luaInterface.unloadTable();
  }
  
  // Loads and reads Ship Manager table
  if (luaInterface.loadTable(tables.shipManagerParameters)) {
    using namespace ShipManager;
    
    alienTargetingDelay = luaInterface.getValue<int>("alienTargetingDelay");
  
    luaInterface.unloadTable();
  }
  
  
  // Loads and reads UIManager table
  if (luaInterface.loadTable(tables.uiManagerParameters)) {
    using namespace UIManager;
    
    timeRect = luaInterface.getValueSDL<SDL_Rect>("timeRect");
    totalScoreRect = luaInterface.getValueSDL<SDL_Rect>("totalScoreRect");
    shipInfoRect = luaInterface.getValueSDL<SDL_Rect>("shipInfoRect");
    currentPlanetRect = luaInterface.getValueSDL<SDL_Rect>("currentPlanetRect");
    selectedPlanetRect = luaInterface.getValueSDL<SDL_Rect>("selectedPlanetRect");
    
    endScoreCoords = luaInterface.getValueSDL<SDL_Point>("endScoreCoords");
    endNameCoords = luaInterface.getValueSDL<SDL_Point>("endNameCoords");
    
    badColor = luaInterface.getValueSDL<SDL_Color>("badColor");
    goodColor = luaInterface.getValueSDL<SDL_Color>("goodColor");
    warningColor = luaInterface.getValueSDL<SDL_Color>("warningColor");
    
    gameScreenFile = luaInterface.getValue<std::string>("gameScreenFile");
    
    luaInterface.unloadTable();
  }
  
  if (luaInterface.loadTable(tables.planetParameters)) {
    using namespace Planet;
    
    planetTextureFile = luaInterface.getValue<std::string>("planetTextureFile");
    planetTexSize = luaInterface.getValue<int>("planetTexSize");
    
    planetOutlineFile = luaInterface.getValue<std::string>("planetOutlineFile");
    planetOutlineSize = luaInterface.getValue<int>("planetOutlineSize");
    
    minFertility = luaInterface.getValue<int>("minFertility");
    fertilityRange = luaInterface.getValue<int>("maxFertility") - minFertility;
    minDeposits = luaInterface.getValue<int>("minDeposits");
    depositsRange = luaInterface.getValue<int>("maxDeposits") - minDeposits;
    startInfraPercent = luaInterface.getValue<int>("startInfraPercent");
    startReservePercent = 100 - startInfraPercent;
    startMiningPercent = luaInterface.getValue<int>("startMiningPercent");
    startFarmingPercent = 100 - startMiningPercent;
    
    homeStartPopulation = luaInterface.getValue<int>("homeStartPopulation");
    homeStartFertility = luaInterface.getValue<int>("homeStartFertility");
    homeStartDeposits = luaInterface.getValue<int>("homeStartDeposits");
    homeStartMiningPercent = luaInterface.getValue<int>("homeStartMiningPercent");
    homeStartFarmingPercent = 100 - homeStartMiningPercent;
    homeStartInfraPercent = luaInterface.getValue<int>("homeStartInfraPercent");
    homeStartReservePercent = 100 - homeStartInfraPercent;
    
    growthPeriod = luaInterface.getValue<int>("growthPeriod");
    starveRate = luaInterface.getValue<double>("starveRate");
    minBirthMultiplier = luaInterface.getValue<double>("minBirthMultiplier");
    birthMultiplierRange = luaInterface.getValue<double>("maxBirthMultiplier") - minBirthMultiplier;
    minDeathMultiplier = luaInterface.getValue<double>("minDeathMultiplier");
    birthMultiplierRange = luaInterface.getValue<double>("maxDeathMultiplier") - minDeathMultiplier;
    
    foodRqmt = luaInterface.getValue<double>("foodRqmt");
    miningRate = luaInterface.getValue<double>("miningRate");
    farmingRate = luaInterface.getValue<double>("farmingRate");
    fertDecay = luaInterface.getValue<double>("fertDecay");
    fertDecayDelay = luaInterface.getValue<int>("fertDecayDelay");
    infrastructureCost = luaInterface.getValue<double>("infrastructureCost");
    
    plagueRate = luaInterface.getValue<double>("plagueRate");
    blightRate = luaInterface.getValue<double>("blightRate");
    mineCollapseRate = luaInterface.getValue<double>("mineCollapseRate");
    alienInvasionRate = luaInterface.getValue<double>("alienInvasionRate");
    
    plagueMultiplier = luaInterface.getValue<double>("plagueMultiplier");
    blightMultiplier = luaInterface.getValue<double>("blightMultiplier");
    mineCollapseMultiplier = luaInterface.getValue<double>("mineCollapseMultiplier");
    
    luaInterface.unloadTable();
  }

  
  if (luaInterface.loadTable(tables.shipParameters)) {
    using namespace Ship;
    
    playerTexFile = luaInterface.getValue<std::string>("playerTexFile");
    alienTexFile = luaInterface.getValue<std::string>("alienTexFile");
    
    shipRect = luaInterface.getValueSDL<SDL_Rect>("shipRect");
    totalCrew = luaInterface.getValue<int>("totalCrew");
    
    speed = luaInterface.getValue<int>("speed");
    alienSpeed = luaInterface.getValue<double>("alienSpeed");
    turnSpeed = luaInterface.getValue<int>("turnSpeed");
  
    luaInterface.unloadTable();
  }
  
  if (luaInterface.loadTable("ui")) {
    using namespace UI;
    
    if (luaInterface.loadTable("eventPanel")) {
      using namespace EventPanel;
      
      panelRect = luaInterface.getValueSDL<SDL_Rect>("panelRect");
      renderRect = luaInterface.getValueSDL<SDL_Rect>("renderRect");
      textBoxesRect = luaInterface.getValueSDL<SDL_Rect>("textBoxesRect");
      
      overprodColor = luaInterface.getValueSDL<SDL_Color>("overprodColor");
      popDeclineColor = luaInterface.getValueSDL<SDL_Color>("popDeclineColor");
      outlineColor = luaInterface.getValueSDL<SDL_Color>("outlineColor");
      
      luaInterface.unloadTable();
    }
    
    if (luaInterface.loadTable("mainMenu")) {
      using namespace MainMenu;
      
      textureFile = luaInterface.getValue<std::string>("textureFile");
      
      startGameButton = luaInterface.getValueSDL<SDL_Rect>("startGameButton");
      scoreboardButton = luaInterface.getValueSDL<SDL_Rect>("scoreboardButton");
      exitGameButton = luaInterface.getValueSDL<SDL_Rect>("exitGameButton");
      
      startGameBorder = luaInterface.getValueSDL<SDL_Rect>("startGameBorder");
      scoreboardBorder = luaInterface.getValueSDL<SDL_Rect>("scoreboardBorder");
      exitGameBorder = luaInterface.getValueSDL<SDL_Rect>("exitGameBorder");
      
      luaInterface.unloadTable();
    }
    
    if (luaInterface.loadTable("scoreboard")) {
      using namespace Scoreboard;
      
      textureFile = luaInterface.getValue<std::string>("textureFile");
      scoresFile = luaInterface.getValue<std::string>("scoresFile");
      
      scoreboardMax = luaInterface.getValue<int>("scoreboardMax");
      
      startingNameBox = luaInterface.getValueSDL<SDL_Rect>("startingNameBox");
      startingScoreBox = luaInterface.getValueSDL<SDL_Rect>("startingScoreBox");
      
      mainMenuButton = luaInterface.getValueSDL<SDL_Rect>("mainMenuButton");
      mainMenuBorder = luaInterface.getValueSDL<SDL_Rect>("mainMenuBorder");
      
      luaInterface.unloadTable();
    }
    
    if (luaInterface.loadTable("endScreen")) {
      using namespace EndScreen;
      
      playAgainButton = luaInterface.getValueSDL<SDL_Rect>("playAgainButton");
      mainMenuButton = luaInterface.getValueSDL<SDL_Rect>("mainMenuButton");
      
      playAgainBorder = luaInterface.getValueSDL<SDL_Rect>("playAgainBorder");
      mainMenuBorder = luaInterface.getValueSDL<SDL_Rect>("mainMenuBorder");
      
      winTextureFile = luaInterface.getValue<std::string>("winTextureFile");
      loseTextureFile = luaInterface.getValue<std::string>("loseTextureFile");
      crashTextureFile = luaInterface.getValue<std::string>("crashTextureFile");
      
      luaInterface.unloadTable();
    }
    
    if (luaInterface.loadTable("textBox")) {
      using namespace TextBox;
      
      color = luaInterface.getValueSDL<SDL_Color>("color");
      fontFile = luaInterface.getValue<std::string>("fontFile");
      regFontSize = luaInterface.getValue<int>("regFontSize");
      eventFontSize = luaInterface.getValue<int>("eventFontSize");
      finalScoreFontSize = luaInterface.getValue<int>("finalScoreFontSize");
      
      wrapLength = luaInterface.getValue<int>("wrapLength");
      scoreboardLine = luaInterface.getValue<int>("scoreboardLine");
      
      luaInterface.unloadTable();
    }
    
    if (luaInterface.loadTable("slider")) {
      using namespace Slider;
      
      baseFilename = luaInterface.getValue<std::string>("baseFilename");
      knobFilename = luaInterface.getValue<std::string>("knobFilename");
      
      baseColor = luaInterface.getValueSDL<SDL_Color>("baseColor");
      knobColor = luaInterface.getValueSDL<SDL_Color>("knobColor");
      
      luaInterface.unloadTable();
    }
    
    if (luaInterface.loadTable("button")) {
      using namespace Button;
      
      textureFile = luaInterface.getValue<std::string>("textureFile");
      
      luaInterface.unloadTable();
    }
    
    luaInterface.unloadTable();
  }

  return true;
}
