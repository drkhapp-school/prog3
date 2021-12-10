#include "PQNode.hpp"
#include <cstddef>
#pragma once
template <typename T> class PriorityQueue {
private:
  PQNode<T> *first;
  size_t count;

public:
  PriorityQueue() {
    first = nullptr;
    count = 0;
  }

  ~PriorityQueue() {
    while (count)
      pop();
  }

  void push(T data, size_t priority) {
    if (!first) {
      first = new PQNode<T>(priority, data);
    } else {
      PQNode<T> *runner = first;
      while (runner->next != nullptr && runner->next->priority <= priority) {
        runner = runner->next;
      }
      runner->next = new PQNode<T>(priority, data, runner->next);
    }
    count++;
  }

  void pop() {
    PQNode<T> *temp = first;
    first = first->next;
    delete temp;
    count--;
  }

  T front() { return first ? first->data : NULL; }
  size_t size() { return count; }
};
