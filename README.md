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

## Rubrics

C++ Capstone Project
README (All Rubric Points REQUIRED)
1-1) A README with instructions is included with the project: The README is included with the project and has instructions for building/running the project. If any additional libraries are needed to run the project, these are indicated with cross-platform installation instructions. You can submit your writeup as markdown or pdf.
-> done

1-2) The README indicates which project is chosen: The README describes the project you have built. The README also indicates the file and class structure, along with the expected behavior or output of the program.
-> done

1-3) The README includes information about each rubric point addressed: The README indicates which rubric points are addressed. The README also indicates where in the code (i.e. files and line numbers) that the rubric points are addressed.
-> done



Compiling and Testing (All Rubric Points REQUIRED)
2-1) The submission must compile and run: The project code must compile and run without errors. We strongly recommend using cmake and make, as provided in the starter repos. If you choose another build system, the code must compile on any reviewer platform.
-> done



Loops, Functions, I/O
3-1) The project demonstrates an understanding of C++ functions and control structures: A variety of control structures are used in the project. The project code is clearly organized into functions.
-> done

3-2) The project reads data from a file and process the data, or the program writes data to a file: The project reads data from an external file or writes data to a file as part of the necessary operation of the program. 
-> "Renderer::UpdateWindowTitle" in the renderer.cpp

3-3) The project accepts user input and processes the input" The project accepts input from a user as part of the necessary operation of the program. 
-> "Controller::Inputhandler" in the controller.cpp



Object Oriented Programming
4-1) The project uses Object Oriented Programming techniques: The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks. 
-> done

4-2) Classes use appropriate access specifiers for class members: All class data members are explicitly specified as public, protected, or private.
-> done

4-3) Class constructors utilize member initialization lists: All class members that are set to argument values are initialized through member initialization lists. 
--> done

4-4) Classes abstract implementation details from their interfaces: All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways. 
--> done

4-5) Classes encapsulate behavior: Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions. 
--> done

4-6) Classes follow an appropriate inheritance hierarchy: Inheritance hierarchies are logical. Composition is used instead of inheritance when appropriate. Abstract classes are composed of pure virtual functions. Override functions are specified. 
-> "class SnakeCommand : public Command" in the snakecommand.h

4-7) Overloaded functions allow the same function to operate on different parameters: One function is overloaded with different signatures for the same function name. 
-> "Snake()" in the snake.h

4-8) Derived class functions override virtual base class functions: One member function in an inherited class overrides a virtual base class member function. 
-> "class SnakeCommand : public Command" in the snakecommand.h

4-9) Templates generalize functions in the project: One function is declared with a template that allows it to accept a generic parameter. 
-> "template <typename T> void IncrementSpeed(T value)" in the snake.h



Memory Management
5-1) The project makes use of references in function declarations: At least two variables are defined as references, or two functions use pass-by-reference in the project code.
-> Controller::Inputhandler in the controller.cpp

5-2) The project uses destructors appropriately: At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor. 
-> done

5-3) The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate: The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction. 
-> done

5-4) The project follows the Rule of 5: For all classes, if any one of the copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor are defined, then all of these functions are defined. 
-> done

5-5) The project uses move semantics to move data, instead of copying it, where possible: For classes with move constructors, the project returns objects of that class by value, and relies on the move constructor, instead of copying the object. 
-> board.cpp line 12

5-6) The project uses smart pointers instead of raw pointers: The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.
-> game.h line 30



Concurrency
6-1) The project uses multithreading: The project uses multiple threads in the execution. 
-> handle_input_thread() in the game.cpp line 54

6-2) A promise and future is used in the project: A promise and future is used to pass data from a worker thread to a parent thread in the project code.
-> "std::future<void> barrier_future = barrier.get_future()" in the game.cpp line 53

6-3) A mutex or lock is used in the project: A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code. -> "std::unique_lock<std::mutex> lck(mtx_)" in the board.cpp line 8

6-4) A condition variable is used in the project: A std::condition_variable is used in the project code to synchronize thread execution. 
-> "std::condition_variable cv" in the game.h line 46