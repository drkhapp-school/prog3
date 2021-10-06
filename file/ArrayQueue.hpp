#include <cstdlib>

template <typename T> class ArrayQueue {
private:
  T *array;
  size_t size;
  size_t count;
  size_t frontIndex;

public:
  ArrayQueue() {}
  ~ArrayQueue() {}

  // Ajoute une donnée à la file.
  void push(T data) {};

  // Enleve une donné de la file.
  void pop() {};
  
  // Retourne la valeur en avant de la file.
  T getFront() {};

  // Retourne la valeur en arrière de la file.
  T getBack() {};

  // Retourne la grosseur de la file.
  size_t getSize() {};
};
