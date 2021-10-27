class Position {
public:
  int x;
  int y;
  bool directions[4];

  Position(int x, int y, bool dir[4]) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < 4; i++) {
      directions[i] = dir[i];
    }
  }

  ~Position() {}
};
