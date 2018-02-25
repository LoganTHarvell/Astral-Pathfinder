//
//  TextureManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "TextureManager.hpp"

// MARK: Libraries and Frameworks
#include <iostream>
#include "SDL2_image/SDL_image.h"

// MARK: Source Files
#include "Game.hpp"


// MARK: - TextureManager Methods

// Loads textures from image file
SDL_Texture *TextureManager::loadTexture(const char *textureFile) {
  
  SDL_Texture *texture = NULL;
  SDL_Surface *tmpSurface = IMG_Load(textureFile);
  
  if (tmpSurface == NULL) {
    std::cerr << "Error loading texture from image at " <<  textureFile
              << " error: " << IMG_GetError() << std::endl;
  }
  else {
    texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
  }
  
  return texture;
}

/*static SDL_Texture *loadTextTexture(_TTF_Font font, const char *text, SDL_Color color) {
  
  SDL_Texture *texture = NULL;
  SDL_Surface *tmpSurface = TTF_RenderText_Solid(font, text, color);
  
  if (tmpSurface == NULL) {
    std::cerr << "Error getting text" << IMG_GetError() << std::endl;
  }
  else {
    texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
  }
  
  return texture;
} */
