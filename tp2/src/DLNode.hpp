/**
 * @file DLNode.hpp
 * @brief Noeud ayant deux liens.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-12-21
 */
#pragma once

template<typename T>
class DLNode {
public:
    T data;
    DLNode<T> *left;
    DLNode<T> *right;

    DLNode(T data, DLNode<T> *left = nullptr, DLNode<T> *right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};
