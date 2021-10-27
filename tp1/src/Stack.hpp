#include "SLNode.hpp"
#include <cstdlib>

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

  size_t size() {
    if (first) {
      size_t result = 1;
      SLNode<T> *runner = first->next;
      while (runner) {
        runner = runner->next;
        result++;
      }
      return result;
    }
    return 0;
  }
};
