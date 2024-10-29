#ifndef FOOD_HPP
#define FOOD_HPP

#include <deque>

#include "constants.hpp"
#include "raylib.h"
#include "raymath.h"

using std::deque;

class Food {
 public:
  Food();
  void draw();
  Vector2 getFoodPos();
  void setFoodPos(deque<Vector2> snakeBody);
  void reset(deque<Vector2> snakeBody);
  ~Food();

 private:
  Vector2 position;
  Texture2D texture;

  Vector2 generateRandomCell();
  Vector2 generateRandomPosition(const deque<Vector2>& snakeBody);
  bool elementInDeque(const deque<Vector2>& body, Vector2 element);
};

#endif  // FOOD_HPP
