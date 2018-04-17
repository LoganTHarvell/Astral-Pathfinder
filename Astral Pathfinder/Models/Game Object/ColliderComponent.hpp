//
//  ColliderComponent.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//

#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include <vector>
#include <experimental/optional>


class ColliderComponent {
  using PointVector = std::vector<SDL_Point>;
  
public:
  // MARK: - Constructors, Destructor
  ColliderComponent() = default;
  ColliderComponent(SDL_Rect r);
  ColliderComponent(SDL_Point center, PointVector vertices);
  ~ColliderComponent() = default;
  
  // MARK: - Game Loop Methods
  void update(SDL_Point center, PointVector vertices);
  
  //MARK: - Collider Methods
  bool collisionAABB(SDL_Rect r);
  bool collisionOBB(PointVector vertices);
  
  PointVector getVertices() { return vertices; };
  static PointVector computeVertices(SDL_Point center, PointVector verticesV,
                                     int angle);
  
  int minAlongAxis(PointVector vertices, SDL_Point axis);
  int maxAlongAxis(PointVector vertices, SDL_Point axis);
  
private:
  // MARK: - Collider Fields
  SDL_Point center;
  PointVector vertices;
  
  // TODO: - Circle collisions?
  std::experimental::optional<int> radius;
  
  // MARK: - Helper Methods
  PointVector rectVertexVectors(SDL_Rect r);
  PointVector getNormals(PointVector vertices);
};


// MARK: - Debug Tools

namespace DebugTools {
  
  void renderVertices(std::vector<SDL_Point> vertices);

}

#endif /* ColliderComponent_hpp */
