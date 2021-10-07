#include <cstdlib>

// Pile statique
template <typename T> class ArrayStack {
private:
  T *array;
  size_t arrayLength;
  size_t topIndex;

public:
  // Constructeur
  ArrayStack(int size) {
    array = new T[size];
    arrayLength = size;
    topIndex = 0;
  }

  // Destructeur
  ~ArrayStack() {
    delete[] array; 
  }

  // Envoyer un donné dans la pile
  void push(T data) {
    if (topIndex < arrayLength)
      array[topIndex++] = data;
  }

  // Enlever un donné de la pile
  void pop() {
    if (topIndex)
      topIndex--;
  }

  // Donner la valeur du dessus de la pile
  T getTop() { return topIndex ? array[topIndex - 1] : NULL; }

  // Donner la grosseur de la pile
  size_t getSize() { return topIndex; }
};
