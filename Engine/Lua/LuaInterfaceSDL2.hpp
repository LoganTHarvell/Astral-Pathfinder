//
//  LuaInterfaceSDL2.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/20/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef LuaInterfaceSDL2_hpp
#define LuaInterfaceSDL2_hpp

// MARK: Libraries and Frameworks
#include "LuaInterface.hpp"
#include "SDL2/SDL.h"
#include <string>


// MARK: - LuaInterfaceSDL2 Class

class LuaInterfaceSDL2 : public LuaInterface {
  
public:
  // MARK: - LuaInterfaceSDL2 Methods
  
  // Alternate method for getting SDL types
  template <typename T> T getValueSDL(const std::string key);
  
private:
  // MARK: - Helper Methods
  int getSDL_RectCoordinate(const std::string key);
  
  // Alternate method for converting SDL_Types
  template <typename T> T convertLuaSDL(const std::string key);
};

#endif /* LuaInterfaceSDL2_hpp */
