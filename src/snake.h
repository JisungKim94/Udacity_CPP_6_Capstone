#ifndef SNAKE_H
#define SNAKE_H

#include "SDL.h"
#include "board.h"
#include "food.h"
#include <mutex>
#include <vector>

class Snake {
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width), grid_height(grid_height),
        head_x(grid_width / 2), head_y(grid_height / 2) {}
  Snake() {}
  Snake(Board *board_);
  Snake(const Snake &source);
  Snake &operator=(const Snake &source);
  Snake(Snake &&source);
  Snake &operator=(Snake &&source);
  ~Snake();

  void AddLife();
  int GetRemainingLifeCount();
  void SetBoard(Board *board_);
  void ChangeDirection(Direction newDirection);
  void Update(Food &food);
  template <typename T> void IncrementSpeed(T value);
  void Die();
  void GrowBody();
  bool GetIsAlive();
  void SetAlive(bool value);

  Direction direction = Direction::kUp;

  float speed{0.2f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  int maxLifeCount{5};
  int lifeCount{0};
  std::vector<SDL_Point> body;
  int GetReward();

private:
  Board *board;
  void UpdateHead(Food &food);
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void Eat(Food &food);
  bool growing{false};
  int grid_width;
  int grid_height;
  int reward{0};
  mutable std::mutex mtx_;
};

#endif