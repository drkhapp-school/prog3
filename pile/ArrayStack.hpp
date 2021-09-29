#include <stdlib.h>

class ArrayStack {
private:
  int *array;
  int size;
  int topIndex;

public:
  // Constructeur
  ArrayStack(int size) {
    array = malloc();
    this->size = size;
    topIndex = 0;
  }

  // Destructeur
  ~ArrayStack() { free(array); }

  // Envoyer un donné dans la pile
  void push(int k) {
    if (topIndex < size)
      array[topIndex++] = k;
  }

  // Enlever un donné de la pile
  void pop() {
    if (topIndex)
      topIndex--;
  }

  // Donner la valeur du dessus de la pile
  int getTop() { return topIndex ? array[topIndex - 1] : NULL; }

  // Donner la grosseur de la pile
  int getSize() { return size; }
};
