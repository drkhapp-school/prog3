/**
 * @file Stack.hpp
 * @brief Pile dynamique.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-12-21
 */
#pragma once
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
    while (count)
      pop();
  }

  void push(T data) {
    first = new SLNode<T>(data, first);
    count++;
  }

  void pop() {
    if (count) {
      SLNode<T> *temp = first;
      first = first->next;
      delete temp;
      count--;
    }
  }

  T top() { return count ? first->data : NULL; }

  size_t size() { return count; }
};
