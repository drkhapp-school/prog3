#include "SLNode.hpp"
#include <cstdlib>
#include <iostream>

template <typename T> class Stack {
private:
  SLNode<T> *first;
  size_t count;

public:
  Stack() {
    first = nullptr;
    count = 0;
  }

  ~Stack() {
    while (first)
      pop();
  }

  void push(T data) {
    first = new SLNode<T>(data, first);
    count++;
  }

  void pop() {
    if (first) {
      SLNode<T> *temp = first;
      first = first->next;
      delete temp;
      count--;
    }
  }

  T top() { return first ? first->data : NULL; }
  size_t size() {}
};
