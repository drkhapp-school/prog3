#include "ArrayStack.hpp"
#include <cstdio>

int main() {
  ArrayStack<int> *pile = new ArrayStack<int>(5);
  pile->push(4);
  pile->push(5);
  printf("Pile: -> Dessus: %i, compte: %lu\n", pile->getTop(), pile->getSize());
  
  delete pile;
  
  ArrayStack<char> pileChar(5);
  pileChar.push('4');
  pileChar.push('l');
  printf("Pile char -> Dessus: %c, compte: %lu\n", pileChar.getTop(), pileChar.getSize());

  return 0;
}
