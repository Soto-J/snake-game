#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <deque>

#include "constants.hpp"
#include "raylib.h"
#include "raymath.h"

using std::deque;

class Snake {
 public:
  bool addSegment{false};
  deque<Vector2> snakeBody{DEFAULT_SNAKE_POSITION};
  Vector2 direction{DEFAULT_SNAKE_DIRECTION};

  void draw();
  void update();
  void reset();
  Vector2 getHeadPos();

 private:
  Vector2 getTail();
};

#endif 
