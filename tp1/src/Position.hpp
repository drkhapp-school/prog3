class Position {
public:
  unsigned char x;
  unsigned char y;
  bool dir[4];

  Position(int x, int y) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < 4; i++)
      this->dir[i] = false;
  }

  ~Position() {}

  int getDirectionCount() {
    int count = 0;
    for (int i = 0; i < 4; i++)
      if (dir[i])
        count++;

    return count;
  }
};
