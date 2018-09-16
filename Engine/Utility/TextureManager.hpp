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
#include <string>


// TODO: - Implement a fully featured texture manager
// URL to helpful resource:
// https://codereview.stackexchange.com/questions/87367/texture-managing

class TextureManager {
  
public:
  // MARK: - TextureManager Methods
  // Loads textures from image file
  static void loadTexture(const std::string textureFile,
                          SDL_Texture **texture, SDL_Renderer *renderer);
  
};

#endif /* TextureManager_hpp */
