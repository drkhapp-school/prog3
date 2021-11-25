/**
 * @file Queue.hpp
 * @brief File dynamique.
 * @author 1927230 - Jean-Philippe 
 * @version 1.0.0
 * @date 2021-11-25
 */
#pragma once
#include "SLNode.hpp"
#include <cstdlib>

template <typename T> class Queue {
private:
  SLNode<T> *first;
  SLNode<T> *last;
  size_t count;

public:
  Queue() {
    first = nullptr;
    last = nullptr;
    count = 0;
  }

  ~Queue() {
    while (first)
      pop();
  }

  void push(T data) {
    if (!last) {
      last = new SLNode<T>(data);
      first = last;
    } else {
      last->next = new SLNode<T>(data);
      last = last->next;
    }
    count++;
  }

  void pop() {
    SLNode<T> *temp = first;
    first = first->next;
    delete temp;

    if (!first)
      last = nullptr;

    count--;
  }

  T front() { return first ? first->data : NULL; }

  T back() { return last ? last->data : NULL; }

  size_t size() {
    size_t count = 0;
    SLNode<T> *runner = first;
    while (runner) {
      runner = runner->next;
      count++;
    }
    return count;
  }
};
