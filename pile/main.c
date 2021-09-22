#include <stdio.h>
#include "pile.h"

int main() {
  push(4);
  push(5);
  push(6);
  push(7);
  pop();
  pop();
  push(65);
  printPile();
  printSize();
  printTop();
  printf("\n");

  pop();
  push(4);
  push(4);
  push(7);
  pop();
  push(6);
  pop();
  printPile();
  printSize();
  printTop();
  printf("\n");

  pop();
  pop();
  pop();
  pop();
  pop();
  pop();
  pop();
  pop();
  pop();
  pop();
  printPile();
  printSize();
  printTop();
  printf("\n");
  return 0;
}
