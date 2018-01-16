//
//  TextureManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 1/15/18.
//  Copyright © 2018 Logan Harvell. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"

class TextureManager {
  
public:
  static SDL_Texture* loadTexture(const char* textureFile);  
};

#endif /* TextureManager_hpp */
