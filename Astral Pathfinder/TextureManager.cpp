//
//  TextureManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

// MARK: Header File
#include "TextureManager.hpp"

// MARK: Libraries and Frameworks
#include "SDL2_image/SDL_image.h"

// MARK: Source Files
#include "Game.hpp"

SDL_Texture* TextureManager::loadTexture(const char *textureFile) {
  SDL_Texture* texture = NULL;
  SDL_Surface* tmpSurface = IMG_Load(textureFile);
  
  if (tmpSurface == NULL) {
    printf("Error loading texture from image at %s", textureFile);
  } else {
    texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
  }
  
  return texture;
}
