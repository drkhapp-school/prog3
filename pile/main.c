#include "ArrayStack.h"
#include <stdio.h>

// Difficilement réutilisable
// -> Crée un fichier.h
// Une seul instance
// -> Crée une structure
// TODO: Limite/gaspille d'espace
// TODO: Robustesse
// TODO: Un seul type de donnée, imposé

int main() {
  struct ArrayStack stackA;
  create(&stackA, 4);
  push(&stackA, 42);
  push(&stackA, 404);
  push(&stackA, 500);
  push(&stackA, 324);
  push(&stackA, 43242);
  printf("Pile A -> Dessus: %i, compte: %i\n", top(&stackA), size(&stackA));
  destroy(&stackA);

  struct ArrayStack stackB;
  create(&stackB, 400);
  push(&stackB, 200);
  printf("Pile B -> Dessus: %i, compte: %i\n", top(&stackB), size(&stackB));
  destroy(&stackB);
  return 0;
}
