-- Configuration file for Astral Pathfinder parameters
local parameters = {

  game = {
    -- Window parameters x, y, w, h
    -- Window x and y can be "centered" in display
    windowRect = { x = "centered", y = "centered", w = 1600, h = 900 },

    fps = 60,                     -- Number of frames per second

    endgameDelay = 120,           -- In number of frames
    timeLimit = (20*60),          -- In number of seconds (x min * 60 sec)
    overtimeFactor = 100,
  },

  planetManager = {
    numberOfPlanets = 25         -- Number of planets in the game
  },

  shipManager = {
    alienTargetingDelay = 60     -- Alien ship seeking delay in frames
  },

  uiManager = {
    timeRect = { x = 115, y = 82, w = 90, h = 36 },
    totalScoreRect = { x = 245, y = 82, w = 90, h = 36 },
    shipInfoRect = { x = 1215, y = 100, w = 320, h = 121 },
    currentPlanetRect = { x = 1215, y = 210, w = 320, h = 240 },
    selectedPlanetRect = { x = 1215, y = 500, w = 320, h = 300 },

    endScoreCoords = { x = 945, y = 335 },
    endNameCoords = { x = 940, y = 480 },

    -- RGB values should be within the range 0 - 255
    badColor = { r = 128, g = 0, b = 0 },
    goodColor = { r = 0, g = 128, b = 0 },
    warningColor = { r = 255, g = 255, b = 0 },

    gameScreenFile = "../Resources/gameScreen2.png"
  },

  planet = {
    -- Planet texture information
    planetTextureFile = "../Resources/planet2.png",
    planetTexSize = 16,

    planetOutlineFile = "../Resources/planetOutline.png",
    planetOutlineSize = 24,

    -- Planet initial attribute information
    -- Percents should be a value between 0 and 100
    minFertility = 20,                -- Mininum value of fertility
    maxFertility = 200,               -- Range = (Max - Min fertility)
    minDeposits = 200,                -- Minium value of deposits
    maxDeposits = 1000,               -- Range = (Max - Min deposits)
    startInfraPercent = 50,
    startMiningPercent = 100,

    -- Homeworld initial attribute values
    homeStartPopulation = 5000,
    homeStartFertility = 100,
    homeStartDeposits = 250,
    homeStartMiningPercent = 58,
    homeStartInfraPercent = 0,

    -- Defines population growth information
    growthPeriod = 1200,            -- Frames per growth period
    starveRate = 0.0008,            -- Starvation deaths per frame
    minBirthMultiplier = 0.05,
    maxBirthMultiplier = 0.2,
    minDeathMultiplier = 0.025,
    maxDeathMultiplier = 0.075,

    -- Defines resource information
    foodRqmt = 0.02,              -- Food required per person
    miningRate = 0.0001,          -- Minerals produced per person per frame
    farmingRate = 0.04,           -- Food produced per person per frame
    fertDecay = 0.0001,
    fertDecayDelay = 10,
    infrastructureCost = 20,      -- Infrastructure per mineral

    -- Random event chances
    plagueRate = 0.05,
    blightRate = 0.1,
    mineCollapseRate = 0.3,
    alienInvasionRate = 0.01,

    -- Random event multipliers
    plagueMultiplier = 1.33,
    blightMultiplier = 0.75,
    mineCollapseMultiplier = 0.5
  },

  ship = {
    -- Filename for player textures
    movingPlayerTex = "../Resources/movingPlayerShip2.png",

    shipRect = { x = 0, y = 0, w = 48, h = 24 },       -- Ship texture info
    totalCrew = 1000,                                  -- Ship Population

    speed = 1,
    alienSpeed = 0.5,
    turnSpeed = 5
  },

  ui = {
    eventPanel = {
      panelRect = { x = 65, y = 175, w = 320, h = 10000 },
      renderRect = { x = 70, y = 180, w = 310, h = 590 },
      textBoxesRect = { x = 0, y = 0, w = 300, h = 0 },

      -- RGB values should be within the range 0 - 255
      overprodColor = { r = 200, g = 0, b = 0 },
      popDeclineColor = { r = 200, g = 200, b = 0 },
      outlineColor = { r = 177, g = 115, b = 6 }
    },

    mainMenu = {
      textureFile = "../Resources/mainMenu.png",
      startGameButton = { x = 600, y = 401, w = 424, h = 57 },
      scoreboardButton = { x = 600, y = 538, w = 424, h = 58 },
      exitGameButton = { x = 600, y = 676, w = 424, h = 54 },
      startGameBorder = { x = 582, y = 390, w = 460, h = 95 },
      scoreboardBorder = { x = 582, y = 527, w = 460, h = 96 },
      exitGameBorder = { x = 582, y = 665, w = 460, h = 92 },
    },

    scoreboard = {
      textureFile = "../Resources/scoreboard.png",
      scoresFile = "Resources/Scores/scoreboard.txt",

      scoreboardMax = 10,

      startingNameBox = { x = 760, y = 203, w = 300, h = 42 },
      startingScoreBox = { x = 880, y = 203, w = 300, h = 42 },
      mainMenuButton = { x = 628, y = 754, w = 376, h = 67 },
      mainMenuBorder = { x = 609, y = 742, w = 412, h = 90 },
    },

    endScreen = {
      playAgainButton = { x = 288, y = 673, w = 424, h = 57 },
      mainMenuButton = { x = 885, y = 677, w = 424, h = 54 },

      playAgainBorder = { x = 270, y = 662, w = 460, h = 95 },
      mainMenuBorder = { x = 867, y = 666, w = 460, h = 92 },

      winTextureFile = "../Resources/winScreen.png",
      loseTextureFile = "../Resources/loseScreen.png",
      alienCrashTextureFile = "../Resources/alienScreen.png"
    },

    textBox = {
      color = { r = 0, g = 128, b = 0 },
      fontFile = "../Resources/MODENINE.TTF",

      regFontSize = 36,
      eventFontSize = 18,
      finalScoreFontSize = 120,

      wrapLength = 300,
      scoreboardLine = 880
    },

    slider = {
      baseFilename = "../Resources/base.png",
      knobFilename = "../Resources/slider.png",

      -- RGB values should be within the range 0 - 255
      baseColor = { r = 150, g = 150, b = 150 },
      knobColor = { r = 0, g = 128, b = 0 }
    },

    button = {
      textureFile = "../Resources/border.png"
    }
  }

}

return parameters
