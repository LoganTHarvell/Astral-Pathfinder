//
//  ColliderComponent.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

#include "SDL2/SDL.h"
#include <vector>


class ColliderComponent {
  
public:
  ColliderComponent() = default;
  ColliderComponent(SDL_Rect r);
  ~ColliderComponent() = default;
  
  SDL_Rect rect;
  
  bool collisionAABB(SDL_Rect r);
  bool collisionOBB(SDL_Rect r, int angle);

  
private:
  // MARK: - Helper Methods
  SDL_Point minAlong(std::vector<SDL_Point> corners);
  SDL_Point maxAlong(std::vector<SDL_Point> corners);
  std::vector<SDL_Point> corners(SDL_Rect r, int angle);
  std::vector<SDL_Point> cornerVectors(SDL_Rect r);
  
};


#endif /* ColliderComponent_hpp */
