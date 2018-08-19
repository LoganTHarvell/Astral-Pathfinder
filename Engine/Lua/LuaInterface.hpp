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


class LuaInterface {
  
public:
  bool init(const std::string filename);
  
  bool loadTable(const std::string key);
  
  template <typename T>
  T getValue(const std::string key);
  void clean();
  
private:
  lua_State *L;
  
  template <typename T>
  T convertLua(const std::string key);
  
  template <typename T>
  T luaDefault();
};


#endif /* LuaInterface_hpp */
