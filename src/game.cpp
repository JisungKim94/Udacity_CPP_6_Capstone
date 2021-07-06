#include "game.h"
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>

#include "SDL.h"
#include "board.h"
#include "food.h"
#include "snake.h"
#include <future>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : food(grid_width, grid_height) {
  board = std::make_unique<Board>(grid_width, grid_height);
  // snake.SetBoard(board.get());
  food.SetBoard(board.get());
  food.SetExpirationTime(7);
  food.Place();
}

void Game::SetSnake(Snake _snake) {
  snake = std::move(_snake);
  snake.SetBoard(board.get());
}

void Game::Inputhandler(std::promise<void> &&barrier,
                        Controller const &controller, Renderer *renderer) {
  controller.Inputhandler(running, snake);
  barrier.set_value();
  cv.notify_all();
}

void Game::Render(Renderer *renderer) {
  renderer->Render(snake);
  renderer->Render(food);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;

  running = true;

  while (true) {
    frame_start = SDL_GetTicks();
    std::promise<void> barrier;
    std::future<void> barrier_future = barrier.get_future();
    std::thread handle_input_thread(&Game::Inputhandler, this,
                                    std::move(barrier), controller, &renderer);
    barrier_future.wait();
    handle_input_thread.join();

    auto handle_update =
        std::async(std::launch::async, &Game::Update, this, &renderer);
    auto handle_render =
        std::async(std::launch::async, &Game::Render, this, &renderer);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    barrier_future.get();
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait_until(
        lck, std::chrono::system_clock::now() + std::chrono::milliseconds(10),
        [this]() { return running == false; });
    if (!running) {
      return;
    }
    handle_update.get();
    handle_render.get();
  }
}

void Game::Update(Renderer *renderer) {
  if (!snake.GetIsAlive()) {
    std::cout << "Score: " << GetScore() << "\n";
    std::cout << "Size: " << GetSize() << "\n";
    return;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  snake.Update(food);
  score += snake.GetReward();
  if (!snake.GetIsAlive()) {
    board->Clear();
    snake.AddLife();
    renderer->GameOver(score, snake.GetRemainingLifeCount());
    score = 0;

    food.Place();
  } else
    food.CheckExpired();
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }