//
//  LuaInterface.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 8/17/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef LuaInterface_hpp
#define LuaInterface_hpp


#include <string>
#include <iostream>

#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"


// MARK: - LuaInterface Class

class LuaInterface {
  
public:
  // MARK: - Initialization Methods
  
  // Initilizes a Lua file with the given filename
  bool init(const std::string filename);
  
  // MARK: - LuaInterface Methods
  
  // Loads a table with given key to the top of the virtual stack
  bool loadTable(const std::string key);
  // Returns a key associated value from the table at the top of the stack
  template <typename T>
  T getValue(const std::string key);
  // Clears virtual stack, leaving only the Lua file's return value
  void clean();
  
private:
  // MARK: - LuaInterface Fields
  
  lua_State *L;
  int numRetVals;
  
  // MARK: - Helper Methods
  
  // Template methods for converting Lua types from the top of the stack
  template <typename T>
  T convertLua(const std::string key);
  template <typename T>
  T luaDefault();
  
};


#endif /* LuaInterface_hpp */
