#include "Maze.hpp"
#include "Window.hpp"
// TODO : Inclusions.

class MazeSolver : public Window {
private:
  Maze *maze;

  // TODO : Déclarations.

public:
  MazeSolver(Maze *maze) {
    this->maze = maze;
    // TODO : Instanciations.
  }

  ~MazeSolver() {
    // TODO : Libérations.
    delete maze;
  }

  void onUpdate() {
    // TODO : Avancer d'un pas.
  }

  void onRefresh() {
    for (int x = 0; x < 53; x++)
      for (int y = 0; y < 53; y++)
        drawSquare(maze->getSquare(x, y), x, y);

    // TODO : Afficher le chemin parcouru.
  }
};
