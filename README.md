# CPPND: Capstone Snake Game Example
The project built is the Snake Game.

Instructions

1. Game : This class implements the GameLoop method case, which is the Run method that calls the three main parts of the game: Inputhandler, Update and Render. This part is on a separate thread.
2. Board : this class, you establish relationships between games with a matrix of points representing possible positions within the game. inside the board can store different kinds of content (FOOD, SNAKEHEAD, SNAKEBODY, EMPTY). Ownership of the Board belongs to the Game class.
3. Snake : Indicates a snake moving inside the related board. For the snake, we store a vector representing the body and a point representing the head. Also we are keeping the direction of using the snake to move on the board. Also we have included the logic to allow the snake to have lifes associated. This is a predetermined value for now. (with the rule of 5)
4. Food : This class represents of Food(score),  it uses 3 foods (NORMAL, PLUS, POISON). the properties are the points where food is stored, and when the snake's head touches food of type POISON, The game is over. Different types of food have different colors and each reward is different. Food has a lifetime associated with it, so when a lifetime expires, it creates new locations and new types of food.
5. Controller : this class we are implementing keyboard input and we delegate the handling of SnakeCommand class which is responsible for changing direction of Snake object when user command is detected
7. Command : An abstract class that defines the command pattern.
8. SnakeCommand : A class that inherits from Command and implements an abstract class for Snake.


This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.
