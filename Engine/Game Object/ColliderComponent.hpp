//
//  ColliderComponent.hpp
//  Astral Pathfinder
//
//  Created by Logan Harvell on 2/27/18.
//  Copyright © 2018 Logan Harvell, Ian Holdeman. All rights reserved.
//
//  Description:
//  Component class for extending a GameObject class. Manages bounding box
//  attributes and enables various types of collision detection for different
//  purposes.

#ifndef ColliderComponent_hpp
#define ColliderComponent_hpp

// MARK: Libraries and Frameworks
#include "SDL2/SDL.h"
#include <vector>
#include <experimental/optional>


// MARK: - ColliderComponent Class

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
  
  bool collisionCircle(int radius, PointVector vertices);
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
  
  // MARK: - Helper Methods
  
  PointVector rectVertexVectors(SDL_Rect r);
  PointVector getNormals(PointVector vertices);
  
};


// MARK: - Debug Tools
// TODO: Move Debug tools to a separate Debug class

namespace DebugTools {
  
  void renderVertices(std::vector<SDL_Point> vertices, SDL_Renderer *renderer);

}

#endif /* ColliderComponent_hpp */
