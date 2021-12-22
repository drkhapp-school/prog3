/**
 * @file PQNode.hpp
 * @brief Noeud de priorité.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-12-01
 */
#include <cstddef>
#pragma once
template <typename T> class PQNode {
public:
  size_t priority;
  T data;
  PQNode<T> *next;

  PQNode(size_t priority, T data, PQNode<T> *next = nullptr) {
    this->priority = priority;
    this->data = data; 
    this->next = next;
  }
};
