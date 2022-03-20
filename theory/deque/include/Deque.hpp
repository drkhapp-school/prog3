#include "SLNode.hpp"
#include <cstdlib>

template <typename T> class Deque {
private:
  SLNode<T> *last;
  size_t count;

public:
  Deque() {
    last = nullptr;
    count = 0;
  }

  ~Deque() {}

  void push_back(T data) {
    if (last) {
      last->next = new SLNode<T>(data, last->next);
      last = last->next;
    } else {
      last = new SLNode<T>(data);
      last->next = last;
    }
    count++;
  }

  void push_front(T data) {
    if (last) {
      last->next = new SLNode<T>(data, last->next);
    } else {
      push_back(data);
    }
    count++;
  }

  void pop_back() {
    if (last) {
      SLNode<T> *temp = last;
      while (last->next != temp)
        last = last->next;

      last->next = temp->next;
      delete temp;
      count--;
    }
  }

  void pop_front() {
    if (last) {
      if (last == last->next) {
        delete last;
        last = nullptr;
      } else {
        SLNode<T> *temp = last->next;
        last->next = temp->next;
        delete temp;
      }
      count--;
    }
  }
  T front() {}
  T back() {}
  size_t size() {}
};
