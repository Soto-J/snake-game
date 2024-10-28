#include <deque>
#include <iostream>
#include <vector>

#include "food/food.hpp"
#include "snake/snake.hpp"

using std::cout, std::deque;

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
    this->checkSelfCollision();
    this->checkOutOfBounce();
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
  bool gameOver{false};

  void checkFoodCollision() {
    Vector2 headPos = this->snake.getHeadPos();
    Vector2 foodPos = this->food.getFoodPos();

    if (Vector2Equals(headPos, foodPos)) {
      this->food.setFoodPos(this->snake.snakeBody);
      this->snake.addSegment = true;
    }
  }

  void checkOutOfBounce() {
    Vector2 headPos = this->snake.getHeadPos();
    bool rowIsInbound = headPos.x < CELL_COUNT && headPos.x >= 0;
    bool colIsInbound = headPos.y < CELL_COUNT && headPos.y >= 0;

    if (rowIsInbound && colIsInbound) {
      return;
    }

    this->GameOver();
  }

  void checkSelfCollision() {
    Vector2 headPos = this->snake.getHeadPos();

    for (size_t i = 1; i < this->snake.snakeBody.size(); i++) {
      if (Vector2Equals(this->snake.snakeBody[i], headPos)) {
        this->GameOver();
      }
    }
  }

  void GameOver() {
    cout << "Is out of BOUNCE!!" << '\n';
    this->gameOver = true;
    this->snake.reset();
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
