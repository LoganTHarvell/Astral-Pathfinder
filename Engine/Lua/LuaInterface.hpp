//
//  LuaInterface.hpp
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


#ifndef LuaInterface_hpp
#define LuaInterface_hpp

// MARK: Libraries and Frameworks
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
#include <string>


// MARK: - LuaInterface Class

class LuaInterface {
  
public:
  
  // MARK: - Initialization Methods
  
  bool init(const std::string filename);
  
  // MARK: - LuaInterface Methods
  
  bool loadTable(const std::string key);
  void unloadTable();
  
  template <typename T> T getValue(const std::string key);
  void clean();
  
protected:
  
  // MARK: - LuaInterface Fields
  
  lua_State *L;
  int luaReturnValCount;
  
  // MARK: - Helper Methods
  
  template <typename T> T convertLua(const std::string key);
  template <typename T> T luaDefault();
  
};


#endif /* LuaInterface_hpp */
