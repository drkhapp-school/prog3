#include <cstdlib>

template <typename T> class ArrayQueue {
private:
  T *array;
  size_t size;
  size_t count;
  size_t frontIndex;

public:
  ArrayQueue(size_t length) {
    array = new T[length];
    size = length;
    frontIndex = count = 0;
  }

  ~ArrayQueue() { delete[] array; }

  // Ajoute une donnée à la file.
  void push(T data) {
    if (count < size) {
      array[(frontIndex + count) % size] = data;
      count++;
    }
  };

  // Enleve une donné de la file.
  void pop() {
    if (count) {
      frontIndex = ++frontIndex % size;
      count--;
    }
  };

  // Retourne la valeur en avant de la file.
  T getFront() { return count ? array[frontIndex] : NULL; };

  // Retourne la valeur en arrière de la file.
  T getBack() { return count ? array[(frontIndex + count - 1) % size] : NULL; };

  // Retourne la grosseur de la file.
  size_t getCount() { return count; };
};
