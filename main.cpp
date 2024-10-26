#include <deque>
#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"

using std::cout, std::deque;

const int SCREEN_WIDTH{750};
const int SCREEN_HEIGHT{750};

const int CELL_SIZE{30};
const int CELL_COUNT{25};

const Color green{173, 204, 96, 255};
const Color darkGreen{43, 51, 24, 255};

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

const deque<Vector2> DEFAULT_SNAKE_POSITION{Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
const Vector2 DEFAULT_SNAKE_DIRECTION{1, 0};

class Snake {
 public:
  bool addSegment{false};

  deque<Vector2> body = DEFAULT_SNAKE_POSITION;
  Vector2 direction = DEFAULT_SNAKE_DIRECTION;

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
    if (this->addSegment) {
      Vector2 tail = this->getTail();
      this->body.push_back(Vector2{tail.x, tail.y});

      this->addSegment = false;
    }

    this->body.pop_back();
    this->body.push_front(Vector2Add(this->getHeadPos(), this->direction));
  }

  void reset() {
    this->body = DEFAULT_SNAKE_POSITION;
    this->direction = DEFAULT_SNAKE_DIRECTION;
  }

  Vector2 getHeadPos() {
    return this->body.front();
  }

 private:
  Vector2 getTail() {
    return this->body.back();
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
      this->food.setFoodPos(this->snake.body);
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
