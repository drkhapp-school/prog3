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

  void push(T data) {};
  void pop() {};
  
  T getFront() {};
  T getBack() {};
  size_t getSize() {};
};
