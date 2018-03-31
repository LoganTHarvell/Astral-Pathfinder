//
//  UIManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "UIManager.hpp"

#include <string>

// MARK: Source Files
#include "TextureManager.hpp"

// MARK: - UIManager Initialization

void UIManager::init() {
  using namespace UiParameters;
  
  time.init(timeRect);
  selectedPlanetInfo.init(selectedPlanetRect);
  DockedPlanetInfo.init(currentPlanetRect);
  shipInfo.init(shipInfoRect);
  hoverBorder = TextureManager::loadTexture("Resources/Assets/border.png");
}

// MARK: - Game Loop Methods

void UIManager::update(Game::State *gameState, PlanetManager *planetManager, ShipManager *shipManager) {
  if (gameState->mainMenu) {
    checkForHovering(gameState);
    if(gameState->mouseDown)
      checkClickedAreaOtherScreen(gameState);
    
    return;
  }
  else if (gameState->endgame == Game::State::quit) {
    gameState->mainMenu = false;
    gameState->isRunning = false;
    return;
  }
  else if (gameState->endgame != Game::State::none){
    gameState->mainMenu = false;
    checkForHovering(gameState);
    if(gameState->mouseDown)
      checkClickedAreaOtherScreen(gameState);

    return;
  }
  
  updateTime(gameState->elapsedTime);
  
  shipInfo.clean();
  shipInfo.setText(shipManager->getPlayerShip());
  
  if (gameState->planetSelected) {
    setSelectedPlanet(planetManager->getSelectedPlanet());
    selectedPlanetWindowCleaned = false;
  }
  else if(!selectedPlanetWindowCleaned) {
    selectedPlanetInfo.clean();
    selectedPlanetWindowCleaned = true;
  }
  
  if(planetManager->planetIsDocked()) {
    setDockedPlanet(planetManager->getDockedPlanet());
    currentPlanetWindowCleaned = false;
  }
  else if(!currentPlanetWindowCleaned) {
    DockedPlanetInfo.clean();
    currentPlanetWindowCleaned = true;
  }
  
  handleMouseDown(gameState, planetManager);
}

void UIManager::render(Game::State *gameState, PlanetManager *pm) {
  using namespace UiParameters;
  if (gameState->mainMenu) {
    if(hoveringLabel == startGame)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    else if(hoveringLabel == scoreboard)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    else if(hoveringLabel == exitGame)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    return;
  }
  else if (gameState->endgame != Game::State::none) {
    // TODO: - Render score
    if(hoveringLabel == playAgain)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    else if(hoveringLabel == endGameExit)
      SDL_RenderCopy(Game::renderer, hoverBorder, NULL, &borderRect);
    return;
  }
  
  time.render(gameState);
  shipInfo.render(gameState);
  
  if(gameState->planetSelected) {
    int selectedPop = pm->getSelectedPlanet().getPopulation();
    selectedPlanetInfo.render(gameState, selectedPop);
  }
  if(gameState->planetCollided) {
    int dockedPop = pm->getDockedPlanet().getPopulation();
    DockedPlanetInfo.render(gameState, dockedPop);
  }
}

// MARK: - UIManager Methods

void UIManager::updateTime(Uint32 elapsedTime) {
  std::string secs = std::to_string(elapsedTime % 60);
  std::string mins = std::to_string(elapsedTime / 60);
  
  time.setMessage("Time " + mins + ":" + secs);
}

void UIManager::setSelectedPlanet(Planet p) {
  selectedPlanetInfo.setUiTextures(p);
}

void UIManager::setDockedPlanet(Planet p) {
  DockedPlanetInfo.setUiTextures(p);
}

void UIManager::handleMouseDown(Game::State *gs, PlanetManager *pm) {
  enum {
    neither, fertilitySlider, reserveSlider
  };
  
  // If mouse button not pressed down, don't check for slider movement
  if(!gs->mouseDown) return;
  
  if(gs->mouseDown)
    checkClickedArea(gs->clickLocation);
  
  // Current Planet Window
  if(currentWindow == currentPlanetWindow) {
    // If down, but not dragging, check if slider was clicked
    if(gs->mouseDown && gs->activeSlider == gs->State::inactive) {
      if(DockedPlanetInfo.checkClick(gs->clickLocation) == fertilitySlider)
        gs->activeSlider = gs->State::currentOne;
      
      if(DockedPlanetInfo.checkClick(gs->clickLocation) == reserveSlider)
        gs->activeSlider = gs->State::currentTwo;
    }
  
    // If so, check mouse movement and adjust slider appropriately
    if(gs->activeSlider == gs->State::currentOne) {
      bool movement = DockedPlanetInfo.moveSlider(gs);
      int percent = DockedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetDepoPercent(100-percent, currentWindow);
        pm->setPlanetFertPercent(percent, currentWindow);
      }
    }
  
    if(gs->activeSlider == gs->State::currentTwo) {
      bool movement = DockedPlanetInfo.moveSlider(gs);
      int percent = DockedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetInfraPercent(100-percent, currentWindow);
        pm->setPlanetReservePercent(percent, currentWindow);
      }
    }
  }
  
  // Selected Planet Window
  if(currentWindow == selectedPlanetWindow) {
    // If down, but not dragging, check if slider was clicked
    if(gs->mouseDown && gs->activeSlider == gs->State::inactive) {
      if(selectedPlanetInfo.checkClick(gs->clickLocation) == fertilitySlider)
        gs->activeSlider = gs->State::selectOne;
      
      if(selectedPlanetInfo.checkClick(gs->clickLocation) == reserveSlider)
        gs->activeSlider = gs->State::selectTwo;
    }
    
    // If so, check mouse movement and adjust slider appropriately
    if(gs->activeSlider == gs->State::selectOne) {
      bool movement = selectedPlanetInfo.moveSlider(gs);
      int percent = selectedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetDepoPercent(100-percent, currentWindow);
        pm->setPlanetFertPercent(percent, currentWindow);
      }
    }
    
    if(gs->activeSlider == gs->State::selectTwo) {
      bool movement = selectedPlanetInfo.moveSlider(gs);
      int percent = selectedPlanetInfo.getSliderPercent();
      
      if(movement) {
        pm->setPlanetInfraPercent(100-percent, currentWindow);
        pm->setPlanetReservePercent(percent, currentWindow);
      }
    }
  }
}

void UIManager::checkClickedArea(SDL_Point p) {
  using namespace UiParameters;
  if((p.x > currentPlanetRect.x) && (p.x < currentPlanetRect.x + currentPlanetRect.w)
     && (p.y > currentPlanetRect.y) && (p.y < currentPlanetRect.y + currentPlanetRect.h))
    currentWindow = currentPlanetWindow;
  
  else if((p.x > selectedPlanetRect.x) && (p.x < selectedPlanetRect.x + selectedPlanetRect.w)
          && (p.y > selectedPlanetRect.y) && (p.y < selectedPlanetRect.y + selectedPlanetRect.h))
    currentWindow = selectedPlanetWindow;
  
  else currentWindow = none;
}

void UIManager::checkForHovering(Game::State *gs) {
  using namespace UiParameters;
  SDL_Point p = gs->dragLocation;
  
  // Main Menu
  if(gs->mainMenu) {
    if((p.x > startGameLabel.x) && (p.x < startGameLabel.x + startGameLabel.w)
       && (p.y > startGameLabel.y) && (p.y < startGameLabel.y + startGameLabel.h)) {
      hoveringLabel = startGame;
      
      if(borderRect.y != startGameLabel.y-11)
        borderRect = {582, 390, 460, 95};
    }
  
    else if((p.x > scoreboardLabel.x) && (p.x < scoreboardLabel.x + scoreboardLabel.w)
            && (p.y > scoreboardLabel.y) && (p.y < scoreboardLabel.y + scoreboardLabel.h)) {
      hoveringLabel = scoreboard;
      
      if(borderRect.y != scoreboardLabel.y-11)
        borderRect = {582, 527, 460, 96};
    }
  
    else if((p.x > exitGameLabel.x) && (p.x < exitGameLabel.x + exitGameLabel.w)
            && (p.y > exitGameLabel.y) && (p.y < exitGameLabel.y + exitGameLabel.h)) {
      hoveringLabel = exitGame;
      
      if(borderRect.y != exitGameLabel.y-11)
        borderRect = {582, 665, 460, 92};
    }
  
    else hoveringLabel = nothing;
  }
  
  // End Screen
  else if(gs->endgame != Game::State::none && gs->endgame != Game::State::quit) {
    if((p.x > playAgainLabel.x) && (p.x < playAgainLabel.x + playAgainLabel.w)
       && (p.y > playAgainLabel.y) && (p.y < playAgainLabel.y + playAgainLabel.h)) {
      hoveringLabel = playAgain;
      
      if(borderRect.y != playAgainLabel.y-11)
        borderRect = {270, 662, 460, 95};
    }
    
    else if((p.x > endGameExitLabel.x) && (p.x < endGameExitLabel.x + endGameExitLabel.w)
            && (p.y > endGameExitLabel.y) && (p.y < endGameExitLabel.y + endGameExitLabel.h)) {
      hoveringLabel = endGameExit;
      
      if(borderRect.y != endGameExitLabel.y-11)
        borderRect = {867, 665, 460, 92};
    }
    
    else hoveringLabel = nothing;
  }
}

void UIManager::checkClickedAreaOtherScreen(Game::State *gs) {
  SDL_Point p = gs->clickLocation;
  using namespace UiParameters;
  
  // Main Menu
  if(gs->mainMenu) {
    if((p.x > startGameLabel.x) && (p.x < startGameLabel.x + startGameLabel.w)
       && (p.y > startGameLabel.y) && (p.y < startGameLabel.y + startGameLabel.h)) {
      hoveringLabel = nothing;
      gs->mainMenu = false;
    }
  
  // Future score board
   /* else if((p.x > scoreboardLabel.x) && (p.x < scoreboardLabel.x + scoreboardLabel.w)
            && (p.y > scoreboardLabel.y) && (p.y < scoreboardLabel.y + scoreboardLabel.h))
    */
  
    else if((p.x > exitGameLabel.x) && (p.x < exitGameLabel.x + exitGameLabel.w)
       && (p.y > exitGameLabel.y) && (p.y < exitGameLabel.y + exitGameLabel.h)) {
      hoveringLabel = nothing;
      gs->mainMenu = false;
      gs->endgame = Game::State::quit;
    }
  }
  
  // End Screen
  else if(gs->endgame != Game::State::none && gs->endgame != Game::State::quit) {
    if((p.x > playAgainLabel.x) && (p.x < playAgainLabel.x + playAgainLabel.w)
       && (p.y > playAgainLabel.y) && (p.y < playAgainLabel.y + playAgainLabel.h)) {
      hoveringLabel = nothing;
      gs->mainMenu = true;
      gs->endgame = Game::State::none;
      gs->restartGame = true;
      gs->mouseDown = false;
    }
    
    else if((p.x > endGameExitLabel.x) && (p.x < endGameExitLabel.x + endGameExitLabel.w)
            && (p.y > endGameExitLabel.y) && (p.y < endGameExitLabel.y + endGameExitLabel.h)) {
      hoveringLabel = nothing;
      gs->mainMenu = false;
      gs->endgame = Game::State::quit;
    }
  }
}
