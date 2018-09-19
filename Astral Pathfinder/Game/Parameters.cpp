//
//  Parameters.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/2/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Assigns default values for all game parameters in Parameter namespace.
//  Organized into groups by class, which match tables in a Lua config file.
//  Load function enables loading parameters from the lua config file.

// MARK: Header File
#include "Parameters.hpp"

// MARK: Libraries and Frameworks
#include "LuaInterfaceSDL2.hpp"
#include <iostream>


// MARK: - Parameter Default Values

namespace Parameters {
  
  // MARK: - Game Default Parameters
  
  namespace Game {
    
    // Window parameters x, y, w, h
    SDL_Rect windowRect = { SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            1600, 900 };

    // Frames per second
    int fps = 60;
    
    // Frame minimum length in ms (1000 ms/fps)
    int frameDelay = 1000/fps;

    // Endgame delay in number of frames
    int endgameDelay = 120;
    
    // Time Values in number of seconds (x min * 60 sec)
    // timeLimitWarning should be less than timeLimit
    int timeLimit = (20*60);
    int timeLimitWarning = (15*60);
   
    // Score decrease per frame of overtime
    int overtimeFactor = 100;
  
  }

  // MARK: - PlanetManager Parameters
  
  namespace PlanetManager {
    
    // Number of planets in the game
    int numberOfPlanets = 25;
  
  }

  // MARK: - ShipManager Parameters
  
  namespace ShipManager {
    
    // Alien ship seeking delay in frames
    Uint32 alienTargetingDelay = 60;
  
  }
  
  // MARK: - UIManager Default Parameters
  
  namespace UIManager {
    
    // Rect values defining main screen position and size
    SDL_Rect screenRect = { 0, 0, Game::windowRect.w, Game::windowRect.h };
    
    // UI element rect geometry in { x, y, w, h }
    SDL_Rect timeRect = { 115, 82, 90, 36 };
    SDL_Rect totalScoreRect = { 245, 82, 90, 36 };
    SDL_Rect shipInfoRect = { 1215, 100, 320, 121 };
    SDL_Rect currentPlanetRect = { 1215, 210, 320, 240 };
    SDL_Rect selectedPlanetRect = { 1215, 500, 320, 300 };
    
    // Screen position for score and name on scoreboard
    SDL_Point endScoreCoords = { 945, 335 };
    SDL_Point endNameCoords = { 940, 480 };
    
    // Color values for UI color coding in { r, g, b } (0 - 255)
    SDL_Color badColor = { 128, 0, 0 };
    SDL_Color goodColor = { 0, 128, 0 };
    SDL_Color warningColor = { 255, 255, 0 };
    
    // File path to main game screen background texture
    std::string gameScreenFile = resourcePath + "gameScreen2.png";
  
  }
 
  // MARK: - Planet Default Parameters
  
  namespace Planet {
    
    // Planet texture information
    std::string planetTextureFile = resourcePath + "planet2.png";
    int planetTexSize = 16;
    std::string planetOutlineFile = resourcePath + "planetOutline.png";
    int planetOutlineSize = 24;
    
    Uint8 normalAlpha = 255;
    SDL_Color selectedColor = { 0, 255, 0 };
    SDL_Color undiscColor = { 200, 200, 200, 150 };
    SDL_Color discoverColor = { 255, 255, 255 };
    SDL_Color colonyColor = { 0, 255, 0, 150 };
    SDL_Color popDecColor = { 200, 200, 0 };
    SDL_Color overprodColor = { 200, 0,  0 };
    
    // Resource information, ranges expressed as (max - min)
    int minFertility = 20;
    int fertilityRange = (200 - minFertility);
    int minDeposits = 200;
    int depositsRange = (1000 - minDeposits);
    
    // Infrastructure and Reserve must sum to 100
    // Set so only infrastructure needs to be assigned a value (0-100)
    int startInfraPercent = 50;
    int startReservePercent = (100 - startInfraPercent);
    
    // Mining and Farming must sum to 100
    // Set so only mining needs to be assigned a value (0-100)
    int startMiningPercent = 100;
    int startFarmingPercent = (100 - startMiningPercent);
    
    // Homeworld initial attribute values
    int homeStartPopulation = 5000;
    int homeStartFertility = 100;
    int homeStartDeposits = 250;
    
    // Mining and Farming must sum to 100, prefer only changing mining (0-100)
    int homeStartMiningPercent = 58;
    int homeStartFarmingPercent = (100 - homeStartMiningPercent);
    int homeStartInfraPercent = 0;
    int homeStartReservePercent = (100 - homeStartInfraPercent);
    
    // Frames per growth period
    int growthPeriod = 1200;
    // Starvation deaths per frame
    float starveRate = 0.0008;
    
    // Population multiplier info, ranges expressed as (max - min)
    float minBirthMultiplier = 0.05;
    float birthMultiplierRange = (0.2 - minBirthMultiplier);
    float minDeathMultiplier = 0.025;
    float deathMultiplierRange = (0.075 - minDeathMultiplier);
    
    // Food required per person
    float foodRqmt = 0.02;
    
    // Minerals produced per person per frame
    float miningRate = 0.0001;
    
    // Food produced per person per frame
    float farmingRate = 0.04;
    
    // Amount of fertility decay per frame
    float fertDecay = 0.0001;
    
    // Fertility decline delay in seconds
    int fertDecayDelay = 10;
    
    // Max population increase per mineral
    float infrastructureCost = 20;
    
    // Random event chances in % chance per event cycle or event
    float plagueRate = 0.05;
    float blightRate = 0.1;
    float mineCollapseRate = 0.3;
    float alienInvasionRate = 0.01;
    
    // Random event multipliers
    float plagueMultiplier = 1.33*(deathMultiplierRange+minDeathMultiplier);
    float blightMultiplier = 0.75;
    float mineCollapseMultiplier = 0.5;
  }
  
  // MARK: - Ship Default Parameters
  
  namespace Ship {
    
    std::string playerTexFile = resourcePath + "movingPlayerShip2.png";
    std::string alienTexFile = resourcePath + "alienShip.png";
    
    // Ship rect geometry in { x, y, w, h }
    SDL_Rect shipRect = { 0, 0, 48, 24 };
    int shipPopulation = 1000;
    
    // Speed in position units per frame
    int speed = 1;
    float alienSpeed = 0.5;
    // Turn speed in rotation degrees per frame
    int turnSpeed = 5;
  
  }
  
  // MARK: - UI Default Parameters
  
  namespace UI {
    // Map Default Parameteres
    namespace Map {
      SDL_Rect rect = { 400, 50, 800, 800 };
      int gridOffset = 50;
    }
    
    // Events Panel Default Parameters
    
    namespace EventPanel {
      
      // UI element rect geometry in { x, y, w, h }
      SDL_Rect panelRect = { 65, 175, 320, 10000 };
      SDL_Rect renderRect = { 70, 180, 310, 590 };
      SDL_Rect textBoxesRect = { 0, 0, 300, 0 };
      
      // Event color coding in { r, g, b } (0-255)
      SDL_Color overprodColor = { 200, 0, 0 };
      SDL_Color popDeclineColor = { 200, 200, 0 };
      SDL_Color outlineColor = { 177, 115, 6 };
    
    }
    
    // Main Menu Defualt Parameters
    
    namespace MainMenu {
      
      std::string textureFile = resourcePath + "mainMenu.png";
      
      // Button selectable geometry in { x, y, w, h }
      SDL_Rect startGameButton = { 600, 401, 424, 57 };
      SDL_Rect scoreboardButton = { 600, 538, 424, 58 };
      SDL_Rect exitGameButton = { 600, 676, 424, 54 };
      
      // Button border geometry in { x, y, w, h }
      SDL_Rect startGameBorder = { 582, 390, 460, 95 };
      SDL_Rect scoreboardBorder = { 582, 527, 460, 96 };
      SDL_Rect exitGameBorder = { 582, 665, 460, 92 };
    
    }
    
    // Scoreboard Default Parameters
    
    namespace Scoreboard {
     
      std::string textureFile = resourcePath + "scoreboard.png";
      std::string scoresFile = resourcePath + "scoreboard.txt";
      
      int scoreboardMax = 10;
      
      SDL_Rect startingNameBox = { 760, 203, 300, 42 };
      SDL_Rect startingScoreBox = { 880, 203, 300, 42 };
      
      // Button selectable geometry in { x, y, w, h }
      SDL_Rect mainMenuButton = { 628, 754, 376, 67 };
      
      // Button border geometry in { x, y, w, h }
      SDL_Rect mainMenuBorder = { 609, 742, 412, 90 };
    
    }
    
    // End Screen Defualt Parameters
    
    namespace EndScreen {
      
      // Button selectable geometry in { x, y, w, h }
      SDL_Rect playAgainButton = { 288, 673, 424, 57 };
      SDL_Rect mainMenuButton = { 885, 677, 424, 54 };
      
      // Button border geometry in { x, y, w, h }
      SDL_Rect playAgainBorder = { 270, 662, 460, 95 };
      SDL_Rect mainMenuBorder = { 867, 666, 460, 92 };
      
      std::string winTextureFile = resourcePath + "winScreen.png";
      std::string loseTextureFile = resourcePath + "loseScreen.png";
      std::string crashTextureFile = resourcePath + "alienScreen.png";
    
    }
    
    // TextBox Default Parameters
    
    namespace TextBox {
      
      // Texture color in { r, g, b } (0-255)
      SDL_Color color = { 0, 128, 0 };
      std::string fontFile = resourcePath + "MODENINE.TTF";
      
      int regFontSize = 36;
      int eventFontSize = 18;
      int finalScoreFontSize = 120;
      
      Uint32 wrapLength = 300;
      int scoreboardLine = 880;
    
    }
  
    // Slider Default Paramters
    
    namespace Slider {
      
      std::string baseTexFile = resourcePath + "base.png";
      std::string sliderTexFile = resourcePath + "slider.png";
      
      // Texture color in { r, g, b } (0-255)
      SDL_Color baseColor = { 150, 150, 150 };
      SDL_Color sliderColor = { 0, 128, 0 };
    
    }
    
    // Button Default Parameters
    
    namespace Button {
      
      std::string textureFile = resourcePath + "border.png";
    
    }
      
  }
  
}


// MARK: - Parameter Loading Functions

/* Lua values are grouped into tables. The format for retrieving values is
 * shown here. Errors are often due to improperly following these steps.
 *
 * 1. Create instance of LuaInterface, use instance for all remaining steps
 * 2. Initialize the lua file with the values with init("filepath")
 * 3. Load a table with loadTable("tablename")
 * 4. Use getValue<type>("valueName") for all values in table (view note below)
 * 5. Unload table by calling unloadTable()
 * 6. Repeat steps 3-5 for all tables with values to be retrieved
 *
 * NOTE #1: If the file contains SDL types, LuaInterfaceSDL must be used, and
 * to retrieve SDL types, use getValueSDL<type>("valueName")
 * NOTE #2: Loaded filenames must prepend the resource filepath
 *
*/

// Loads parameters from Lua config file
bool Parameters::loadParameters() {
  bool flag = true;
  
  LuaInterfaceSDL2 luaInterface = LuaInterfaceSDL2();
    
  // Initializes Lua config file
  if (!luaInterface.init(luaConfigFile)) return false;
  
  // Load, read and converts lua values, then unload for each table
  if (luaInterface.loadTable(tables.gameParameters)) {
    using namespace Game;
    
    windowRect = luaInterface.getValueSDL<SDL_Rect>("windowRect");
    fps = luaInterface.getValue<int>("fps");
    frameDelay = 1000 / Game::fps;
    endgameDelay = luaInterface.getValue<int>("endgameDelay");
    timeLimit = luaInterface.getValue<int>("timeLimit");
    timeLimitWarning = luaInterface.getValue<int>("timeLimitWarning");
    overtimeFactor = luaInterface.getValue<int>("overtimeFactor");
    
    luaInterface.unloadTable();
  }
  else flag = false;

  if (luaInterface.loadTable(tables.planetManagerParameters)) {
    using namespace PlanetManager;
    
    numberOfPlanets = luaInterface.getValue<int>("numberOfPlanets");
 
    luaInterface.unloadTable();
  }
  else flag = false;
  
  if (luaInterface.loadTable(tables.shipManagerParameters)) {
    using namespace ShipManager;
    
    alienTargetingDelay = luaInterface.getValue<int>("alienTargetingDelay");
  
    luaInterface.unloadTable();
  }
  else flag = false;
  
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
    
    gameScreenFile = resourcePath;
    gameScreenFile += luaInterface.getValue<std::string>("gameScreenFile");
    
    luaInterface.unloadTable();
  }
  else flag = false;

  if (luaInterface.loadTable(tables.planetParameters)) {
    using namespace Planet;
    
    planetTextureFile = resourcePath;
    planetTextureFile += luaInterface.getValue<std::string>("planetTextureFile");
    planetTexSize = luaInterface.getValue<int>("planetTexSize");
    
    planetOutlineFile = resourcePath;
    planetOutlineFile += luaInterface.getValue<std::string>("planetOutlineFile");
    planetOutlineSize = luaInterface.getValue<int>("planetOutlineSize");
    
    normalAlpha = luaInterface.getValue<int>("normalAlpha");
    undiscColor = luaInterface.getValueSDL<SDL_Color>("undiscColor");
    discoverColor = luaInterface.getValueSDL<SDL_Color>("discoverColor");
    colonyColor = luaInterface.getValueSDL<SDL_Color>("colonyColor");
    popDecColor = luaInterface.getValueSDL<SDL_Color>("popDecColor");
    overprodColor = luaInterface.getValueSDL<SDL_Color>("overprodColor");
    selectedColor = luaInterface.getValueSDL<SDL_Color>("selectedColor");
    
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
  else flag = false;

  
  if (luaInterface.loadTable(tables.shipParameters)) {
    using namespace Ship;
    
    playerTexFile = resourcePath;
    playerTexFile += luaInterface.getValue<std::string>("playerTexFile");
    alienTexFile = resourcePath;
    alienTexFile += luaInterface.getValue<std::string>("alienTexFile");
    
    shipRect = luaInterface.getValueSDL<SDL_Rect>("shipRect");
    shipPopulation = luaInterface.getValue<int>("shipPopulation");
    
    speed = luaInterface.getValue<int>("speed");
    alienSpeed = luaInterface.getValue<double>("alienSpeed");
    turnSpeed = luaInterface.getValue<int>("turnSpeed");
  
    luaInterface.unloadTable();
  }
  else flag = false;

  if (luaInterface.loadTable("ui")) {
    using namespace UI;
    
    if (luaInterface.loadTable("map")) {
      using namespace Map;
      
      rect = luaInterface.getValueSDL<SDL_Rect>("rect");
      gridOffset = luaInterface.getValue<int>("gridOffset");
      
      luaInterface.unloadTable();
    }
    
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
    else flag = false;

    if (luaInterface.loadTable("mainMenu")) {
      using namespace MainMenu;
      
      textureFile = resourcePath;
      textureFile += luaInterface.getValue<std::string>("textureFile");
      
      startGameButton = luaInterface.getValueSDL<SDL_Rect>("startGameButton");
      scoreboardButton = luaInterface.getValueSDL<SDL_Rect>("scoreboardButton");
      exitGameButton = luaInterface.getValueSDL<SDL_Rect>("exitGameButton");
      
      startGameBorder = luaInterface.getValueSDL<SDL_Rect>("startGameBorder");
      scoreboardBorder = luaInterface.getValueSDL<SDL_Rect>("scoreboardBorder");
      exitGameBorder = luaInterface.getValueSDL<SDL_Rect>("exitGameBorder");
      
      luaInterface.unloadTable();
    }
    else flag = false;

    if (luaInterface.loadTable("scoreboard")) {
      using namespace Scoreboard;
      
      textureFile = resourcePath;
      textureFile += luaInterface.getValue<std::string>("textureFile");
      scoresFile = resourcePath;
      scoresFile += luaInterface.getValue<std::string>("scoresFile");
      
      scoreboardMax = luaInterface.getValue<int>("scoreboardMax");
      
      startingNameBox = luaInterface.getValueSDL<SDL_Rect>("startingNameBox");
      startingScoreBox = luaInterface.getValueSDL<SDL_Rect>("startingScoreBox");
      
      mainMenuButton = luaInterface.getValueSDL<SDL_Rect>("mainMenuButton");
      mainMenuBorder = luaInterface.getValueSDL<SDL_Rect>("mainMenuBorder");
      
      luaInterface.unloadTable();
    }
    else flag = false;

    if (luaInterface.loadTable("endScreen")) {
      using namespace EndScreen;
      
      playAgainButton = luaInterface.getValueSDL<SDL_Rect>("playAgainButton");
      mainMenuButton = luaInterface.getValueSDL<SDL_Rect>("mainMenuButton");
      
      playAgainBorder = luaInterface.getValueSDL<SDL_Rect>("playAgainBorder");
      mainMenuBorder = luaInterface.getValueSDL<SDL_Rect>("mainMenuBorder");
      
      winTextureFile = resourcePath;
      winTextureFile += luaInterface.getValue<std::string>("winTextureFile");
      loseTextureFile = resourcePath;
      loseTextureFile += luaInterface.getValue<std::string>("loseTextureFile");
      crashTextureFile = resourcePath;
      crashTextureFile += luaInterface.getValue<std::string>("crashTextureFile");
      
      luaInterface.unloadTable();
    }
    else flag = false;

    if (luaInterface.loadTable("textBox")) {
      using namespace TextBox;
      
      color = luaInterface.getValueSDL<SDL_Color>("color");
      fontFile = resourcePath;
      fontFile += luaInterface.getValue<std::string>("fontFile");
      regFontSize = luaInterface.getValue<int>("regFontSize");
      eventFontSize = luaInterface.getValue<int>("eventFontSize");
      finalScoreFontSize = luaInterface.getValue<int>("finalScoreFontSize");
      
      wrapLength = luaInterface.getValue<int>("wrapLength");
      scoreboardLine = luaInterface.getValue<int>("scoreboardLine");
      
      luaInterface.unloadTable();
    }
    else flag = false;

    if (luaInterface.loadTable("slider")) {
      using namespace Slider;
      
      baseTexFile = resourcePath;
      baseTexFile += luaInterface.getValue<std::string>("baseTexFile");
      sliderTexFile = resourcePath;
      sliderTexFile += luaInterface.getValue<std::string>("sliderTexFile");
      
      baseColor = luaInterface.getValueSDL<SDL_Color>("baseColor");
      sliderColor = luaInterface.getValueSDL<SDL_Color>("sliderColor");
      
      luaInterface.unloadTable();
    }
    else flag = false;

    if (luaInterface.loadTable("button")) {
      using namespace Button;
      
      textureFile = resourcePath;
      textureFile += luaInterface.getValue<std::string>("textureFile");
      
      luaInterface.unloadTable();
    }
    else flag = false;

    luaInterface.unloadTable();
  }

  return true;
}
