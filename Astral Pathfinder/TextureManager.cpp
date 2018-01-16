//
//  TextureManager.cpp
//  SDL_Test
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#include "TextureManager.hpp"

#include "SDL2_image/SDL_image.h"

#include "Game.hpp"

SDL_Texture* TextureManager::loadTexture(const char *textureFile) {
  SDL_Surface* tmpSurface = IMG_Load(textureFile);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
  SDL_FreeSurface(tmpSurface);
  
  return texture;
}
