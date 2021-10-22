#pragma once

enum class Square { WAY, WALL, ENTRY, EXIT, PATH };

class Maze {
private:
  Square maze[2809];

public:
  Maze(const unsigned char &mazeId);

  const Square &getSquare(const unsigned char &x, const unsigned char &y);
};
