//
//  LuaInterfaceSDL2.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/20/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

// MARK: Header File
#include "LuaInterfaceSDL2.hpp"

// MARK: Libraries and Frameworks
#include <iostream>


// MARK: - LuaInterfaceSDL2 Methods

template <typename T>
T LuaInterfaceSDL2::getValueSDL(const std::string key) {

  // Verifies a file is loaded
  if(!L) {
    std::cerr << "Error: no file loaded" << std::endl;
    return T();
  }
  
  // Pushes value with given key to top of stack, else throws error
  if (!lua_getfield(L, -1, key.c_str())) {
    std::cerr << "Error: value for \"" << key << "\" not found" << std::endl;
    lua_pop(L, 1);
    return T();
  }
  
  T value;
  value = convertLuaSDL<T>(key);
  lua_pop(L, 1);
  
  return value;
}


// MARK: - Helper Methods

int LuaInterfaceSDL2::getSDL_RectCoordinate(const std::string key) {

  int x = 0;
  lua_getfield(L, -1, key.c_str());

  // Checks for special case position values of SDL_Rect
  if (!lua_isnumber(L, -1) && lua_isstring(L, -1)) {
    std::string xs = convertLua<std::string>(key);

    if (xs == "centered") {
      x = SDL_WINDOWPOS_CENTERED;
    }
    else {
      std::cerr << "Error \"" << xs
                << "\" not an option for SDL_Rect position value" << std::endl;
    }

  }
  else {
    x = convertLua<int>(key);
  }

  lua_pop(L, 1);

  return x;
}


// MARK: Template Specializations for SDL2 Types

template <>
SDL_Point LuaInterfaceSDL2::convertLuaSDL<SDL_Point>(const std::string key) {
  
  // Reports error if value with given key is not a table
  if (!lua_istable(L, -1)) {
    std::cerr << "Error: cannot convert\"" << key
    <<  "\" to SDL_Point" << std::endl;
  }
  
  int x = getSDL_RectCoordinate("x");
  int y = getSDL_RectCoordinate("y");
  
  SDL_Point p = { x, y };
  
  return p;
}

template <>
SDL_Rect LuaInterfaceSDL2::convertLuaSDL<SDL_Rect>(const std::string key) {

  // Reports error if value with given key is not a table
  if (!lua_istable(L, -1)) {
    std::cerr << "Error: cannot convert\"" << key
    <<  "\" to SDL_Rect" << std::endl;
  }
  
  int x = getSDL_RectCoordinate("x");
  int y = getSDL_RectCoordinate("y");
  int w = getValue<int>("w");
  int h = getValue<int>("h");
  
  SDL_Rect r = { x, y, w, h };
  
  return r;
  
}

template <>
SDL_Color LuaInterfaceSDL2::convertLuaSDL<SDL_Color>(const std::string key) {
  
  // Reports error if value with given key is not a table
  if (!lua_istable(L, -1)) {
    std::cerr << "Error: cannot convert\"" << key
    <<  "\" to SDL_Color" << std::endl;
  }
  
  Uint8 r = getValue<int>("r");
  Uint8 g = getValue<int>("g");
  Uint8 b = getValue<int>("b");
  
  SDL_Color c = { r, g, b };
  
  return c;
  
}

// MARK: - Explicit Instantions for Template Methods

template SDL_Point LuaInterfaceSDL2::getValueSDL<SDL_Point>(const std::string key);
template SDL_Rect LuaInterfaceSDL2::getValueSDL<SDL_Rect>(const std::string key);
template SDL_Color LuaInterfaceSDL2::getValueSDL<SDL_Color>(const std::string key);
