#include "snake.hpp"

#include "constants.hpp"

// PUBLIC
void Snake::draw() {
  for (Vector2 body : this->snakeBody) {
    Rectangle rectangle = {
        float(body.x * CELL_SIZE),
        float(body.y * CELL_SIZE),
        float(CELL_SIZE),
        float(CELL_SIZE),
    };

    DrawRectangleRounded(rectangle, 0.5, 50, darkGreen);
  }
};

void Snake::update() {
  if (this->addSegment) {
    Vector2 tail = this->getTail();
    this->snakeBody.push_back(Vector2{tail.x, tail.y});

    this->addSegment = false;
  }

  this->snakeBody.pop_back();
  this->snakeBody.push_front(Vector2Add(this->getHeadPos(), this->direction));
};

void Snake::reset() {
  this->snakeBody = DEFAULT_SNAKE_POSITION;
  this->direction = DEFAULT_SNAKE_DIRECTION;
};

Vector2 Snake::getHeadPos() {
  return this->snakeBody.front();
};

// PRIVATE
Vector2 Snake::getTail() {
  return this->snakeBody.back();
}