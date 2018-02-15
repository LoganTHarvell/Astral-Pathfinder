//
//  TextureManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell, Ian Holdeman on 1/15/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"


class TextureManager {
  
public:
  // MARK: - TextureManager Methods
  // Loads textures from image file
  static SDL_Texture *loadTexture(const char *textureFile);
  
};

#endif /* TextureManager_hpp */
