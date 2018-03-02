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
#include <experimental/optional>


// TODO: Generalize class for any game object
class ColliderComponent {
  using Vector = std::vector<SDL_Point>;
  
public:
  ColliderComponent() = default;
  ColliderComponent(SDL_Rect r);
  ColliderComponent(SDL_Point center, Vector vertices);
  ~ColliderComponent() = default;
  
  void update(SDL_Point center, Vector vertices);
  Vector getVertices() { return vertices; };
  
  bool collisionAABB(SDL_Rect r);
  bool collisionOBB(Vector vertices);

  SDL_Point minAlongXY(Vector corners);
  SDL_Point maxAlongXY(Vector corners);
  
  static Vector computeVertices(SDL_Point center, Vector verticesV, int angle);
  
private:
  SDL_Point center;
  Vector vertices;
  
  SDL_Point min;
  SDL_Point max;
  
  std::experimental::optional<int> radius;
  
  // MARK: - Helper Methods
  Vector rectVertexVectors(SDL_Rect r);
  
};


#endif /* ColliderComponent_hpp */
