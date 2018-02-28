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

// TODO: Generalize class for any game object
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
  SDL_Point minAlongXY(std::vector<SDL_Point> corners);
  SDL_Point maxAlongXY(std::vector<SDL_Point> corners);
  std::vector<SDL_Point> shipVertices(SDL_Rect r, int angle);
  std::vector<SDL_Point> shipVertexVectors(SDL_Rect r);
  
};


#endif /* ColliderComponent_hpp */
