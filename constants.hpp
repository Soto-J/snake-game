#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <deque>

#include "raylib.h"

const int SCREEN_WIDTH{750};
const int SCREEN_HEIGHT{750};

const int CELL_SIZE{30};
const int CELL_COUNT{25};

const Color darkGreen{43, 51, 24, 255};
const Color green{173, 204, 96, 255};

const std::deque<Vector2> DEFAULT_SNAKE_POSITION{
    Vector2{6, 9},
    Vector2{5, 9},
    Vector2{4, 9},
};

const Vector2 DEFAULT_SNAKE_DIRECTION{1, 0};

#endif  // CONSTANTS_HPP
