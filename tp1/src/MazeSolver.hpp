#include "Maze.hpp"
#include "Position.hpp"
#include "Stack.hpp"
#include "Window.hpp"

class MazeSolver : public Window {
private:
  Maze *maze;
  Stack<Position *> *path;

  void setDirections() {
    Position *pos = path->top();
    pos->dir[0] = maze->getSquare(pos->x, pos->y + 1) != Square::WALL;
    pos->dir[1] = maze->getSquare(pos->x, pos->y - 1) != Square::WALL;
    pos->dir[2] = maze->getSquare(pos->x - 1, pos->y) != Square::WALL;
    pos->dir[3] = maze->getSquare(pos->x + 1, pos->y) != Square::WALL;
  }

public:
  MazeSolver(Maze *maze) {
    this->maze = maze;
    this->path = new Stack<Position *>;

    for (int x = 0; x < 53; x++)
      for (int y = 0; y < 53; y++)
        if (maze->getSquare(x, y) == Square::ENTRY) {
          path->push(new Position(x, y));
          setDirections();
          x = y = 53;
        }
  }

  ~MazeSolver() {
    delete maze;
    while (path->size()) {
      delete path->top();
      path->pop();
    }
    delete path;
  }

  void onUpdate() {
    Position *current = path->top();

    if (maze->getSquare(current->x, current->y) == Square::EXIT)
      return;

    // Déterminer la direction à prendre
    unsigned char direction = 0;
    switch (current->getDirectionCount()) {
    case 0:
      delete current;
      return path->pop();
    case 1:
      while (current->dir[direction] == false)
        direction++;
      break;
    default:
      do
        direction = rand() % 4;
      while (current->dir[direction] == false);
      break;
    }

    current->dir[direction] = false;
    unsigned char provenance;
    switch (direction) {
    case 0:
      path->push(new Position(current->x, current->y + 1));
      provenance = 1;
      break;
    case 1:
      path->push(new Position(current->x, current->y - 1));
      provenance = 0;
      break;
    case 2:
      path->push(new Position(current->x - 1, current->y));
      provenance = 3;
      break;
    case 3:
      path->push(new Position(current->x + 1, current->y));
      provenance = 2;
      break;
    }
    setDirections();
    path->top()->dir[provenance] = false;
  }

  void onRefresh() {
    for (int x = 0; x < 53; x++)
      for (int y = 0; y < 53; y++)
        drawSquare(maze->getSquare(x, y), x, y);

    drawSquare(Square::PATH, path->top()->x, path->top()->y);
  }
};
