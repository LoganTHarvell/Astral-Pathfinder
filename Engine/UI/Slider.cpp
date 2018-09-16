//
//  Slider.cpp
//  Astral Pathfinder
//
//  Created by Ian Holdeman on 3/3/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  A UI element that represents a ratio through a slider along a base. This
//  class handles initializing, updating, and rendering the slider. It also
//  enables getting and setting the attributes like position and corresponding
//  percentage.

// MARK: Header File
#include "Slider.hpp"

// MARK: Libraries and FrameWorks
#include "TextureManager.hpp"


// MARK: - Slider Initialization

void Slider::init(SDL_Rect rectOne, SDL_Rect rectTwo) {
  
  base = rectOne;
  slider = rectTwo;
  
}


// MARK: - Game Loop Methods

void Slider::update() {
  
}

void Slider::render(SDL_Renderer *renderer) {
  SDL_RenderCopy(renderer, baseTexture, NULL, &base);
  SDL_RenderCopy(renderer, sliderTexture, NULL, &slider);
}

void Slider::clean() {
  if (baseTexture == nullptr && sliderTexture == nullptr) return;
  
  if (baseTexture != nullptr) {
    SDL_DestroyTexture(baseTexture);
    baseTexture = nullptr;
  }
  
  if (sliderTexture != nullptr) {
    SDL_DestroyTexture(sliderTexture);
    sliderTexture = nullptr;
  }
}


// MARK: - Slider Methods

bool Slider::isInitialized() {
  if (baseTexture != nullptr && sliderTexture != nullptr) return true;
  else return false;
}


void Slider::setTextures(std::string baseFile, std::string sliderFile,
                         SDL_Renderer *renderer, int percent) {
  clean();
  
  TextureManager::loadTexture(baseFile, &baseTexture, renderer);
  TextureManager::loadTexture(sliderFile, &sliderTexture, renderer);

  updateSliderPosition(percent);
}

void Slider::colorMod(SDL_Color base, SDL_Color slider) {
  SDL_SetTextureColorMod(baseTexture, base.r, base.g, base.b);
  SDL_SetTextureColorMod(sliderTexture, slider.r, slider.g, slider.b);
}

// Sets slider position based on a given percentage it should represent
void Slider::updateSliderPosition(int percent) {
  float p = static_cast<float>(percent);
  float scale = base.w/100.0f;
  
  slider.x = static_cast<int>(p*scale)+base.x-(slider.w/2);
}

// Sets slider position along the base
void Slider::setSliderPosition(int pos) {
  int tmp = pos-(slider.w/2) + base.x;
  if (tmp <= base.x + base.w) slider.x = tmp;
}

// Gets the percentage represented by the position of the slider along the base
int Slider::getPercent() {
  int temp = (slider.x+(slider.w/2)) - base.x;
  return static_cast<int>(temp / (base.w/100.0f));
}
