//
//  LuaInterface.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/17/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "LuaInterface.hpp"


bool LuaInterface::init(const std::string filename) {
  
  if (L) lua_close(L);    // Closes any existing lua state
  L = luaL_newstate();    // Creates new lua state
  
  if (!L) return false;   // Exits if lua state allocation failed
  
  luaL_openlibs(L);       // Opens auxiliary Lua libraries

  // Loads and runs file, closes lua state in case of errors
  if (luaL_dofile(L, filename.c_str())) {
    std::cerr << "Error loading \"" << filename << "\"" << std::endl;
    lua_close(L);
    return false;
  }
  
  return true;
}


bool LuaInterface::loadTable(const std::string key) {
  
  lua_pushstring(L, key.c_str());
  lua_gettable(L, -2);
  
  if (!lua_istable(L, -1)) {
    std::cerr << "Error: failed to load table \"" << key << "\"" << std::endl;
    return false;
  }
  
  return true;
}


// MARK: - Template Definitions

template <typename T>
T LuaInterface::getValue(const std::string key) {
  
  if(!L) {
    std::cerr << "No file loaded" << std::endl;
    return luaDefault<T>();
  }
  
  lua_getfield(L, -1, key.c_str());
  
  T value;
  value = convertLua<T>(key);
  
  lua_pop(L, 1);
  
  return value;
}


// MARK: - Template Specializations

template <typename T>
T LuaInterface::convertLua(const std::string key) {
  return 0;
}

template <>
bool LuaInterface::convertLua<bool>(const std::string key) {
  if (!lua_isboolean(L, -1)) {
    std::cerr << "Error converting \"" << key << "\" to a bool" << std::endl;
  }
  
  return static_cast<bool>(lua_toboolean(L, -1));
}

template <>
int LuaInterface::convertLua<int>(const std::string key) {
  if (!lua_isnumber(L, -1)) {
    std::cerr << "Error converting \"" << key << "\" to an int" << std::endl;
  }
  
  return static_cast<int>(lua_tointeger(L, -1));
}

template <>
double LuaInterface::convertLua<double>(const std::string key) {
  if (!lua_isnumber(L, -1)) {
    std::cerr << "Error converting \"" << key << "\" to a double" << std::endl;
  }
  
  return static_cast<double>(lua_tonumber(L, -1));
}

template <>
std::string LuaInterface::convertLua<std::string>(const std::string key) {
  if (!lua_isstring(L, -1)) {
    std::cerr << "Error converting \"" << key << "\" to a string" << std::endl;
  }
  
  return static_cast<std::string>(lua_tostring(L, -1));
}


template <typename T>
T LuaInterface::luaDefault() {
  return 0;
}


// MARK: - Explicit Instantiations for Template Methods

template bool LuaInterface::getValue<bool>(const std::string key);
template int LuaInterface::getValue<int>(const std::string key);
template double LuaInterface::getValue<double>(const std::string key);
template std::string LuaInterface::getValue<std::string>(const std::string key);
