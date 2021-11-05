/**
 * @file Stack.hpp
 * @brief Pile dynamique.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-11-05
 */
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

  /**
   * @brief Ajouter une donnée à la pile
   *
   * @param data la donnée que l'on veut ajouter
   */
  void push(T data) {
    first = new SLNode<T>(data, first);
    count++;
  }

  /**
   * @brief Enlever une donnée de la pile.
   */
  void pop() {
    if (count) {
      SLNode<T> *temp = first;
      first = first->next;
      delete temp;
      count--;
    }
  }

  /**
   * @return La valeur au dessus de la pile.
   */
  T top() { return count ? first->data : NULL; }

  /**
   * @return La taille de la pile.
   */
  size_t size() { return count; }
};
