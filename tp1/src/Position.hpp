/**
 * @file Position.hpp
 * @brief Classe d'une position dans le labyrinthe.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-11-05
 */
class Position {
public:
  unsigned char x;
  unsigned char y;
  bool dir[4];

  Position(unsigned char x, unsigned char y) {
    this->x = x;
    this->y = y;
    for (unsigned char i = 0; i < 4; i++)
      this->dir[i] = false;
  }

  ~Position() {}

  /**
   * @brief Détermine le nombre de direction qui sont possible d'aller.
   *
   * @return le nombre de position possible
   */
  unsigned char getDirectionCount() {
    unsigned char count = 0;
    for (unsigned char i = 0; i < 4; i++)
      if (dir[i])
        count++;

    return count;
  }
};
