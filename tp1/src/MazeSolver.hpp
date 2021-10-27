#include "Maze.hpp"
#include "Position.hpp"
#include "Stack.hpp"
#include "Window.hpp"

class MazeSolver : public Window {
private:
  Maze *maze;
  Stack<Position *> *stack;

public:
  MazeSolver(Maze *maze) {
    this->maze = maze;
    this->stack = new Stack<Position *>;

    for (int x = 0; x < 53; x++)
      for (int y = 0; y < 53; y++)
        if (maze->getSquare(x, y) == Square::ENTRY) {
          Position *entry = new Position(x, y);
          setDirections(entry);
          stack->push(entry);
        }
  }

  ~MazeSolver() {
    delete maze;
    delete stack;
  }

  void setDirections(Position *pos) {
    pos->dir[0] = maze->getSquare(pos->x, pos->y + 1) != Square::WALL;
    pos->dir[1] = maze->getSquare(pos->x, pos->y - 1) != Square::WALL;
    pos->dir[2] = maze->getSquare(pos->x - 1, pos->y) != Square::WALL;
    pos->dir[3] = maze->getSquare(pos->x + 1, pos->y) != Square::WALL;
  }

  void onUpdate() {
    int direction = 0;
    int currentX = stack->top()->x;
    int currentY = stack->top()->y;

    if (maze->getSquare(currentX, currentY) == Square::EXIT)
      return;

    if (stack->top()->getDirectionCount() == 0)
      return stack->pop();

    if (stack->top()->getDirectionCount() == 1) {
      while (!stack->top()->dir[direction])
        direction++;
    } else {
      do {
        direction = rand() % 4;
      } while (!stack->top()->dir[direction]);
    }

    stack->top()->dir[direction] = false;
    Position *newPosition;

    switch (direction) {
    case 0:
      newPosition = new Position(currentX, currentY + 1);
      setDirections(newPosition);
      newPosition->dir[1] = false;
      break;
    case 1:
      newPosition = new Position(currentX, currentY - 1);
      setDirections(newPosition);
      newPosition->dir[0] = false;
      break;
    case 2:
      newPosition = new Position(currentX - 1, currentY);
      setDirections(newPosition);
      newPosition->dir[3] = false;
      break;
    case 3:
      newPosition = new Position(currentX + 1, currentY);
      setDirections(newPosition);
      newPosition->dir[2] = false;
      break;
    }
    stack->push(newPosition);
  }

  void onRefresh() {
    for (int x = 0; x < 53; x++)
      for (int y = 0; y < 53; y++)
        drawSquare(maze->getSquare(x, y), x, y);

    drawSquare(Square::PATH, stack->top()->x, stack->top()->y);
  }
};
