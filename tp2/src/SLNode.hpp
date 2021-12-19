/**
 * @file SLNode.hpp
 * @brief Noeud ayant un lien.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-12-21
 */
#pragma once

template <typename T> class SLNode {
public:
  T data;
  SLNode<T> *next;

  SLNode(T data, SLNode<T> *next = nullptr) {
    this->data = data;
    this->next = next;
  }
};
