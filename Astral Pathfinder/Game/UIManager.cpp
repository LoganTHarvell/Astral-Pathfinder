//
//  UIManager.cpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/21/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#include "UIManager.hpp"
#include <string>

void UIManager::init() {
  depositsBox.initDeposits();
  fertilityBox.initFertility();
}

void UIManager::update() {
  
}

void UIManager::render() {
  depositsBox.render();
  fertilityBox.render();
}

void UIManager::setText(int deposits, int fertility) {
  std::string depo = "Deposits: " + std::to_string(deposits);
  std::string fert = "Fertility: " + std::to_string(fertility);
  
  depositsBox.setMessage(depo.c_str());
  fertilityBox.setMessage(fert.c_str());
}
