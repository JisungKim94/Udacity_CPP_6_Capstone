#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "snakecommand.h"
class Controller {
public:
  void Inputhandler(bool &running, Snake &snake) const;

private:
};

#endif