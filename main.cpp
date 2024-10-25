#include <deque>
#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"

using std::cout, std::deque;

const int SCREEN_WIDTH = 750;
const int SCREEN_HEIGHT = 750;

const int CELL_SIZE = 30;
const int CELL_COUNT = 25;

const Color green = {173, 204, 96, 255};
const Color darkGreen = {43, 51, 24, 255};

class Food {
 public:
  Food() : position(this->generateRandomCell()) {
    Image img = LoadImage("graphics/food.png");
    this->texture = LoadTextureFromImage(img);  // Texture2D (Data type for GPU processing)
    UnloadImage(img);
  }

  void draw() {
    DrawTexture(  // (150 x 180)
        this->texture,
        this->position.x * CELL_SIZE,
        this->position.y * CELL_SIZE,
        WHITE);
  }

  Vector2 getFoodPos() {
    return this->position;
  }

  void setFoodPos(deque<Vector2> snakeBody) {
    this->position = this->generateRandomPosition(snakeBody);
  }

  Vector2 generateRandomPosition(const deque<Vector2>& snakeBody) {
    Vector2 newRandomPosition;

    do {
      newRandomPosition = this->generateRandomCell();
    } while (this->elementInDeque(snakeBody, newRandomPosition));

    return newRandomPosition;
  }

  ~Food() {
    UnloadTexture(texture);
  }

 private:
  Vector2 position;
  Texture2D texture;

  Vector2 generateRandomCell() {
    float randomX = GetRandomValue(0, CELL_COUNT - 1);
    float randomY = GetRandomValue(0, CELL_COUNT - 1);

    return Vector2{randomX, randomY};
  }

  bool elementInDeque(const deque<Vector2>& body, Vector2 element) {
    for (Vector2 b : body) {
      if (Vector2Equals(b, element)) {
        return true;
      }
    }

    return false;
  }
};

class Snake {
 public:
  deque<Vector2> body{Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
  Vector2 direction{1, 0};

  void draw() {
    for (Vector2 bodyPos : this->body) {
      Rectangle rectangle = {
          (float)bodyPos.x * CELL_SIZE,
          (float)bodyPos.y * CELL_SIZE,
          (float)CELL_SIZE,
          (float)CELL_SIZE};

      DrawRectangleRounded(rectangle, 0.5, 50, darkGreen);
    }
  }

  void update() {
    this->body.pop_back();
    this->body.push_front(Vector2Add(this->getHeadPos(), this->direction));
  }

  Vector2 getHeadPos() {
    return this->body[0];
  }
};

class Game {
 public:
  Snake snake = Snake();
  Food food = Food();

  void draw() {
    this->snake.draw();
    this->food.draw();
  }

  void update() {
    this->snake.update();
    this->checkFoodCollision();
  }

  void userKeyPressed() {
    if (IsKeyPressed(KEY_UP) && snake.direction.y != 1) {
      snake.direction = {0, -1};
    }

    if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1) {
      snake.direction = {0, 1};
    }

    if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1) {
      snake.direction = {-1, 0};
    }

    if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1) {
      snake.direction = {1, 0};
    }
  }

 private:
  void checkFoodCollision() {
    Vector2 headPos = this->snake.getHeadPos();
    Vector2 foodPos = this->food.getFoodPos();

    if (Vector2Equals(headPos, foodPos)) {
      cout << "Eating Food" << '\n';

      this->food.setFoodPos(this->snake.body);
    }
  }
};

// HELPER FUNCTION
double lastUpdateTime = 0;
bool eventTriggered(double interval) {
  double currentTime = GetTime();

  if (currentTime - lastUpdateTime >= interval) {
    lastUpdateTime = currentTime;
    return true;
  }

  return false;
}

int main(int, char**) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Retro Snake");  // (w, h, label)
  SetTargetFPS(60);

  Game game = Game();

  while (!WindowShouldClose()) {  // Detects window close / ESC key
    BeginDrawing();

    if (eventTriggered(0.4)) {
      game.update();
    }

    game.userKeyPressed();

    // Draw
    DrawText("Welcome to my first Sname Game!", 190, 200, 20, LIGHTGRAY);
    ClearBackground(green);

    game.draw();

    EndDrawing();
  }

  CloseWindow();  // De-Initialization: Close window and OpenGL context
}
