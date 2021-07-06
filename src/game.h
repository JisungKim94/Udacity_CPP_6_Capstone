#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "board.h"
#include "controller.h"
#include "food.h"
#include "renderer.h"
#include "snake.h"
#include <atomic>
#include <condition_variable>
#include <future>
#include <memory>
#include <mutex>
#include <random>

class Game {
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void SetSnake(Snake _snake);

private:
  Snake snake;
  Food food;
  // SDL_Point food;
  std::unique_ptr<Board> board;
  bool running;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void Update(Renderer *renderer);
  void Inputhandler(std::promise<void> &&barrier, Controller const &controller,
                    Renderer *renderer);
  void Render(Renderer *renderer);
  void RenderWindowTitle(Renderer);

  std::condition_variable cv;

  std::mutex mtx;
};

#endif