#include "ArrayStack.hpp"
#include <cstdio>

int main() {
  ArrayStack *pileA = new ArrayStack(5);
  pileA->push(4);
  pileA->push(5);

  printf("Pile A: -> Dessus: %i, compte: %i\n", pileA->getTop(),
         pileA->getSize());

  delete pileA;

  return 0;
}
