/**
 * @file BSTree.hpp
 * @brief Arbre binaire de recherche.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-12-21
 */
#pragma once
#include "DLNode.hpp"
#include "Queue.hpp"

enum Traversal { Prefix,
                 Infix,
                 Postfix,
                 ReverseInfix };

template<typename T>
class BSTree {
private:
    DLNode<T> *root;
    size_t count;

    void infixTraversal(DLNode<T> *node, Queue<T> *result) {
        if (node->left)
            infixTraversal(node->left, result);
        result->push(node->data);
        if (node->right)
            infixTraversal(node->right, result);
    }

    void reverseInfixTraversal(DLNode<T> *node, Queue<T> *result) {
        if (node->right)
            reverseInfixTraversal(node->right, result);
        result->push(node->data);
        if (node->left)
            reverseInfixTraversal(node->left, result);
    }

    void prefixTraversal(DLNode<T> *node, Queue<T> *result) {
        result->push(node->data);
        if (node->left)
            prefixTraversal(node->left, result);
        if (node->right)
            prefixTraversal(node->right, result);
    }

    void postfixTraversal(DLNode<T> *node, Queue<T> *result) {
        if (node->left)
            postfixTraversal(node->left, result);
        if (node->right)
            postfixTraversal(node->right, result);
        result->push(node->data);
    }

    void add(DLNode<T> *node, T data) {
        if (data < node->data) {
            if (node->left) {
                add(node->left, data);
            } else {
                node->left = new DLNode<T>(data);
                count++;
            }
        } else if (data > node->data) {
            if (node->right) {
                add(node->right, data);
            } else {
                node->right = new DLNode<T>(data);
                count++;
            }
        }
    }

public:
    BSTree() {
        root = nullptr;
        count = 0;
    }

    ~BSTree() { clear(); }

    void clear() {
        while (count)
            remove(root->data);
    }

    void add(T data) {
        if (root) {
            add(root, data);
        } else {
            root = new DLNode<T>(data);
            count++;
        }
    }

    Queue<T> *traversal(Traversal type) {
        Queue<T> *result = new Queue<T>();
        if (root)
            switch (type) {
                case Prefix:
                    prefixTraversal(root, result);
                    break;
                case Infix:
                    infixTraversal(root, result);
                    break;
                case Postfix:
                    postfixTraversal(root, result);
                    break;
                case ReverseInfix:
                    reverseInfixTraversal(root, result);
            }
        return result;
    }

    void remove(T data) {
        // Aucune donnée
        if (!root)
            return;

        enum Path { Left,
                    Right,
                    Root };
        DLNode<T> *parent = root;
        DLNode<T> *node = nullptr;
        Path side;

        // Trouver la feuille à supprimer
        while (!node) {
            if (data < parent->data) {
                if (!parent->left)
                    return;
                // Donnée à gauche
                if (parent->left->data == data) {
                    side = Left;
                    node = parent->left;
                } else {
                    parent = parent->left;
                }
            } else if (data > parent->data) {
                if (!parent->right)
                    return;
                // Donnée à droite
                if (parent->right->data == data) {
                    side = Right;
                    node = parent->right;
                } else {
                    parent = parent->right;
                }
            }
            // Donnée à la racine
            else {
                side = Root;
                node = root;
            }
        }

        // 2 feuilles
        if (node->left && node->right) {
            DLNode<T> *child = node->left;
            T newData;

            while (child->right)
                child = child->right;

            newData = child->data;
            remove(newData);
            node->data = newData;
        }

        // Zéro ou une feuille
        else {
            switch (side) {
                // Feuille gauche
                case Left:
                    if (!node->left && !node->right)
                        parent->left = nullptr;
                    else
                        parent->left = node->left ?: node->right;
                    break;

                // Feuille droite
                case Right:
                    if (!node->left && !node->right)
                        parent->right = nullptr;
                    else
                        parent->right = node->left ?: node->right;
                    break;

                // Racine
                case Root:
                    if (!node->left && !node->right)
                        root = nullptr;
                    else
                        root = node->left ?: node->right;
                    break;
            }

            delete node;
            count--;
        }
    }

    bool search(T data) {
        DLNode<T> *runner = root;
        while (runner) {
            if (data < runner->data)
                runner = runner->left;
            else if (data > runner->data)
                runner = runner->right;
            else
                return true;
        }
        return false;
    }

    T top() { return root ? root->data : NULL; }
};
