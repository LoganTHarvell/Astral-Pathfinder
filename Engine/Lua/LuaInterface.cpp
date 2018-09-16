//
//  LuaInterface.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/17/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  An interface between C++ and Lua that uses the Lua C API to make function
//  calls to the libraries enabling the loading and reading of Lua scripts.
//  The interface also enables retrieving values from Lua tables and converting
//  the values to native C++ types.

// MARK: Header File
#include "LuaInterface.hpp"

// MARK: Libraries and Frameworks
#include <iostream>


// MARK: - Initialization Methods

bool LuaInterface::init(const std::string filename) {
  
  if (L) lua_close(L);    // Closes any existing lua state
  L = luaL_newstate();
  luaReturnValCount = 0;
  
  if (!L) return false;   // Exits if lua state allocation failed
  
  luaL_openlibs(L);       // Opens auxiliary Lua libraries

  // Loads and runs file, closes lua state in case of errors
  if (luaL_dofile(L, filename.c_str())) {
    std::cerr << "Error loading \"" << filename << "\"" << std::endl;
    lua_close(L);
    return false;
  }
  
  // Sets a count of values returned by Lua file
  luaReturnValCount = lua_gettop(L);
  
  return true;
}


// MARK: - LuaInterface Methods

bool LuaInterface::loadTable(const std::string key) {
  
  lua_getfield(L, -1, key.c_str());   // Pushes table with key to top of stack
  
  // Verifies top of stack is table
  if (!lua_istable(L, -1)) {
    std::cerr << "Error: \"" << key << "\" not a table" << std::endl;
    lua_pop(L, 1);
    return false;
  }
  
  return true;
}

void LuaInterface::unloadTable() {
  // Pops any non-table elements
  while (!lua_istable(L, -1)) lua_pop(L, 1);
  
  // If the table is not a script return value, pops the table from the stack
  if (lua_gettop(L) > luaReturnValCount) lua_pop(L, 1);
  else std::cerr << "Error: no table to unload" << std::endl;
}

void LuaInterface::clean() {
  // Pops all elements added to stack since initialization
  int n = lua_gettop(L) - luaReturnValCount;
  lua_pop(L, n);
}

// MARK: Template Definitions

template <typename T>
T LuaInterface::getValue(const std::string key) {
  
  // Verifies a file is loaded
  if(!L) {
    std::cerr << "Error: no file loaded" << std::endl;
    return luaDefault<T>();
  }
  
  // Pushes value with given key to top of stack, else throws error
  if (!lua_getfield(L, -1, key.c_str())) {
    std::cerr << "Error: value for \"" << key << "\" not found" << std::endl;
    lua_pop(L, 1);
    return luaDefault<T>();
  }
  
  T value;
  value = convertLua<T>(key);
  lua_pop(L, 1);                  // Pops retrieved value from top of stack
  
  return value;
}


// MARK: - Helper Methods

// MARK: Template Definitions

template <typename T>
T LuaInterface::convertLua(const std::string key) {
  return 0;
}

template <typename T>
T LuaInterface::luaDefault() {
  return T();
}

// MARK: Template Specializations

template <>
bool LuaInterface::convertLua<bool>(const std::string key) {
  if (!lua_isboolean(L, -1)) {
    std::cerr << "Error: cannot convert \"" << key
              << "\" to a bool" << std::endl;
  }
  
  return static_cast<bool>(lua_toboolean(L, -1));
}

template <>
int LuaInterface::convertLua<int>(const std::string key) {
  if (!lua_isnumber(L, -1)) {
    std::cerr << "Error: cannot convert \"" << key
              << "\" to an int" << std::endl;
  }
  
  return static_cast<int>(lua_tointeger(L, -1));
}

template <>
double LuaInterface::convertLua<double>(const std::string key) {
  if (!lua_isnumber(L, -1)) {
    std::cerr << "Error: cannot convert \"" << key
              << "\" to a double" << std::endl;
  }
  
  return static_cast<double>(lua_tonumber(L, -1));
}

template <>
std::string LuaInterface::convertLua<std::string>(const std::string key) {
  if (!lua_isstring(L, -1)) {
    std::cerr << "Error: cannot convert \"" << key
              << "\" to an string" << std::endl;
  }
  
  return static_cast<std::string>(lua_tostring(L, -1));
}


// MARK: - Explicit Instantiations for Template Methods

template bool LuaInterface::getValue<bool>(const std::string key);
template int LuaInterface::getValue<int>(const std::string key);
template double LuaInterface::getValue<double>(const std::string key);
template std::string LuaInterface::getValue<std::string>(const std::string key);
