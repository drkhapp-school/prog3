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

  init(&stackA);
  push(&stackA, 42);
  push(&stackA, 404);

  printf("Pile A -> Dessus: %i, compte: %i\n", top(&stackA), size(&stackA));
  struct ArrayStack stackB;

  init(&stackB);
  push(&stackB, 200);

  printf("Pile B -> Dessus: %i, compte: %i\n", top(&stackB), size(&stackB));
  return 0;
}
