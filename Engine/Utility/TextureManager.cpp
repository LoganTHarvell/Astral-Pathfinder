//
//  TextureManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  A utility class for managing textures objects. Handles loading a texture
//  from a file.

// MARK: Header File
#include "TextureManager.hpp"

// MARK: Libraries and Frameworks
#include "SDL2_image/SDL_image.h"
#include <iostream>


// MARK: - TextureManager Methods

// Loads textures from image file
void TextureManager::loadTexture(const std::string textureFile,
                                 SDL_Texture **texture, SDL_Renderer *renderer) {
  
  if (texture != nullptr) {
    SDL_DestroyTexture(*texture);
    *texture = nullptr;
  }
  
  SDL_Surface *tmpSurface = IMG_Load(textureFile.c_str());
  
  if (tmpSurface == nullptr) {
    std::cerr << "Error loading texture from image at " <<  textureFile
              << " error: " << IMG_GetError() << std::endl;
  }
  else {
    *texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
  }
  
}
