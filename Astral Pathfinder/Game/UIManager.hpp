//
//  UIManager.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef UIManager_hpp
#define UIManager_hpp

#include "Text.hpp"

class UIManager {
  
public:
  void init();
  
  void update();
  void render();
  void setText(int deposits, int fertility);
  
private:
  Text depositsBox, fertilityBox;
  
};

#endif /* UIManager_hpp */
