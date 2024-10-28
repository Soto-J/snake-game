#include "food.hpp"

#include <iostream>

Food::Food() : position(this->generateRandomCell()) {
  Image img = LoadImage("../graphics/food.png");
  this->texture = LoadTextureFromImage(img);

  if (img.data == nullptr) {
    std::cerr << "Failed to load image 'graphics/food.png'" << std::endl;
  }
  UnloadImage(img);

}

void Food::draw() {
  DrawTexture(
      this->texture,
      int(this->position.x * CELL_SIZE),
      int(this->position.y * CELL_SIZE),
      WHITE);
}

Vector2 Food::getFoodPos() {
  return this->position;
};

void Food::setFoodPos(deque<Vector2> snakeBody) {
  this->position = this->generateRandomPosition(snakeBody);
};

Food::~Food() {
  UnloadTexture(this->texture);
};

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