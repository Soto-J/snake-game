#include "food.hpp"

#include <iostream>

// PUBLIC
Food::Food() : _position(this->generateRandomCell()) {
  Image img = LoadImage("../graphics/food.png");
  this->_texture = LoadTextureFromImage(img);

  UnloadImage(img);
}

void Food::draw() {
  DrawTexture(
      this->_texture,
      int(this->_position.x * CELL_SIZE),
      int(this->_position.y * CELL_SIZE),
      WHITE);
}

Vector2 Food::getFoodPos() {
  return this->_position;
};

void Food::setFoodPos(deque<Vector2> snakeBody) {
  this->_position = this->generateRandomPosition(snakeBody);
};

void Food::reset(deque<Vector2> snakeBody) {
  this->setFoodPos(snakeBody);
};

Food::~Food() {
  UnloadTexture(this->_texture);
};

// PRIVATE
Vector2 Food::generateRandomCell() {
  float randomX = float(GetRandomValue(0, CELL_COUNT - 1));
  float randomY = float(GetRandomValue(0, CELL_COUNT - 1));

  return Vector2{randomX, randomY};
}

Vector2 Food::generateRandomPosition(const deque<Vector2>& snakeBody) {
  Vector2 newRandomPosition;

  do {
    newRandomPosition = this->generateRandomCell();
  } while (this->elementInDeque(snakeBody, newRandomPosition));

  return newRandomPosition;
};

bool Food::elementInDeque(const deque<Vector2>& body, Vector2 element) {
  for (Vector2 b : body) {
    if (Vector2Equals(b, element)) {
      return true;
    }
  }
  return false;
}