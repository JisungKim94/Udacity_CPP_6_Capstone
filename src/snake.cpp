#include "snake.h"
#include "game.h"
#include <cmath>
#include <iostream>
#include <mutex>

Snake::Snake(Board *board_)
    : grid_width(board_->width), grid_height(board_->height),
      head_x(board_->width / 2), head_y(board_->height / 2) {}

Snake::Snake(const Snake &source) {
  // std::cout << "Snake Copy Constructor" << std::endl;
  std::unique_lock<std::mutex> lck(mtx_);
  std::unique_lock<std::mutex> lck_src(source.mtx_);
  speed = source.speed;
  grid_height = source.grid_height;
  grid_width = source.grid_width;
  size = source.size;
  alive = source.alive;
  head_x = source.head_x;
  head_y = source.head_y;
  body = source.body;
  growing = source.growing;
  board = source.board;
}

Snake::~Snake() {}

Snake::Snake(Snake &&source) {
  // std::cout << "Snake Move Constructor" << std::endl;
  std::unique_lock<std::mutex> lck(mtx_);
  std::unique_lock<std::mutex> lck_src(source.mtx_);
  grid_height = source.grid_height;
  grid_width = source.grid_width;
  speed = source.speed;
  size = source.size;
  alive = source.alive;
  head_x = source.head_x;
  head_y = source.head_y;
  body = std::move(source.body);
  growing = source.growing;
  board = source.board;
  source.board = nullptr;
}

Snake &Snake::operator=(const Snake &source) {
  if (this == &source)
    return *this;
  // std::cout << "Snake Assignment Copy Operator" << std::endl;
  std::unique_lock<std::mutex> lck(mtx_);
  std::unique_lock<std::mutex> lck_src(source.mtx_);
  grid_height = source.grid_height;
  grid_width = source.grid_width;
  speed = source.speed;
  size = source.size;
  alive = source.alive;
  head_x = source.head_x;
  head_y = source.head_y;
  body = source.body;
  growing = source.growing;
  board = source.board;
  return *this;
}

Snake &Snake::operator=(Snake &&source) {
  // std::cout << "Snake Assignment Move Operator" << std::endl;
  if (this == &source)
    return *this;
  std::unique_lock<std::mutex> lck(mtx_);
  std::unique_lock<std::mutex> lck_src(source.mtx_);
  grid_height = source.grid_height;
  grid_width = source.grid_width;
  speed = source.speed;
  size = source.size;
  alive = source.alive;
  head_x = source.head_x;
  head_y = source.head_y;
  body = std::move(source.body);
  growing = source.growing;
  board = source.board;
  source.board = nullptr;
  return *this;
}

void Snake::SetBoard(Board *board_) {
  board = board_;
  board->SetCellValue(static_cast<int>(grid_width / 2),
                      static_cast<int>(grid_height / 2),
                      Board::CellContent::SnakeHead);
}

void Snake::AddLife() {
  std::unique_lock<std::mutex> lck(mtx_);
  lifeCount++;
  if (lifeCount > maxLifeCount)
    return;
  board->SetCellValue(static_cast<int>(grid_width / 2),
                      static_cast<int>(grid_height / 2),
                      Board::CellContent::SnakeHead);
  size = 1;
  speed = 0.2f;
  alive = true;
}

void Snake::ChangeDirection(Snake::Direction newDirection) {
  Snake::Direction opposite;
  switch (newDirection) {
  case Snake::Direction::kDown:
    opposite = Snake::Direction::kUp;
    break;
  case Snake::Direction::kUp:
    opposite = Snake::Direction::kDown;
    break;
  case Snake::Direction::kLeft:
    opposite = Snake::Direction::kRight;
    break;
  case Snake::Direction::kRight:
    opposite = Snake::Direction::kLeft;
    break;
  }
  std::unique_lock<std::mutex> lck(mtx_);
  if (direction != opposite || size == 1)
    direction = newDirection;
  return;
}
template <typename T> void Snake::IncrementSpeed(T value) {
  std::unique_lock<std::mutex> lck(mtx_);
  speed += value;
}

void Snake::Update(Food &food) {

  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.

  UpdateHead(food);

  if (!GetIsAlive()) {
    std::cout << "Snake die !!!" << std::endl;
    return;
  }

  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {

    UpdateBody(current_cell, prev_cell);
  }
}

int Snake::GetReward() {
  std::unique_lock<std::mutex> lck(mtx_);
  return reward;
}

void Snake::Eat(Food &food) {
  reward = 0;
  switch (food.GetFoodType()) {
  case Food::FoodType::Poison:
    Die();
    break;
  case Food::FoodType::Normal:
    IncrementSpeed(0.001);
    reward++;
    GrowBody();
    break;
  case Food::FoodType::Plus:
    IncrementSpeed(0.002);
    reward += 2;
    GrowBody();
    break;
  }
}

bool Snake::GetIsAlive() {
  std::unique_lock<std::mutex> lck(mtx_);
  return alive;
}

void Snake::SetAlive(bool value) {
  std::unique_lock<std::mutex> lck(mtx_);
  alive = value;
}

void Snake::UpdateHead(Food &food) {
  std::unique_lock<std::mutex> lck(mtx_);
  reward = 0;
  switch (direction) {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
  int new_head_board_x = static_cast<int>(head_x);
  int new_head_board_y = static_cast<int>(head_y);
  switch (board->GetCellValue(new_head_board_x, new_head_board_y)) {
  case Board::CellContent::SnakeBody:
    lck.unlock();
    Die();
    break;
  case Board::CellContent::FoodKind:
    lck.unlock();
    board->SetCellValue(new_head_board_x, new_head_board_y,
                        Board::CellContent::SnakeHead);
    Eat(food);
    food.Place();
    break;
  case Board::CellContent::Empty:
    board->SetCellValue(new_head_board_x, new_head_board_y,
                        Board::CellContent::SnakeHead);
    break;
  }
}

int Snake::GetRemainingLifeCount() {
  std::unique_lock<std::mutex> lck(mtx_);
  return maxLifeCount - lifeCount;
}

void Snake::UpdateBody(SDL_Point &current_head_cell,
                       SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  std::unique_lock<std::mutex> lck(mtx_);
  board->SetCellValue(prev_head_cell.x, prev_head_cell.y,
                      Board::CellContent::SnakeBody);

  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    board->SetCellValue((*body.begin()).x, (*body.begin()).y,
                        Board::CellContent::Empty);
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }
}

void Snake::Die() {
  std::unique_lock<std::mutex> lck(mtx_);
  alive = false;
  body.clear();
}

void Snake::GrowBody() {
  std::unique_lock<std::mutex> lck(mtx_);
  growing = true;
}
