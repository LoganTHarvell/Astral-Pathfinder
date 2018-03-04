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


// TODO: Generalize class for any game object
class ColliderComponent {
  using Vector = std::vector<SDL_Point>;
  
public:
  // MARK: - Constructors, Destructor
  ColliderComponent() = default;
  ColliderComponent(SDL_Rect r);
  ColliderComponent(SDL_Point center, Vector vertices);
  ~ColliderComponent() = default;
  
  // MARK: - Game Loop Methods
  void update(SDL_Point center, Vector vertices);
  
  //MARK: - Collider Methods
  bool collisionAABB(SDL_Rect r);
  bool collisionOBB(Vector vertices, int angle);
  
  Vector getVertices() { return vertices; };
  static Vector computeVertices(SDL_Point center, Vector verticesV, int angle);
  
  std::vector<std::vector<double>> getAxes(int angle);
  int minAlongAxis(Vector vertices, std::vector<double> axis);
  int maxAlongAxis(Vector vertices, std::vector<double> axis);
  
private:
  // MARK: - Collider Fields
  SDL_Point center;
  Vector vertices;
  
  std::experimental::optional<int> radius;
  
  // MARK: - Helper Methods
  Vector rectVertexVectors(SDL_Rect r);
};


#endif /* ColliderComponent_hpp */
