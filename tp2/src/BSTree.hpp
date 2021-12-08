/**
 * @file BSTree.hpp
 * @brief Arbre binaire de recherche.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-11-25
 */
#include "DLNode.hpp"
#include <cstdlib>
#include <iostream>
#include <queue>

using namespace ::std;

enum Traversal { Prefix, Infix, Postfix, Breathfirst };

template <typename T> class BSTree {
private:
  DLNode<T> *root;
  size_t count;

  void infixTraversal(DLNode<T> *node, queue<T> *result) {
    if (node->left)
      infixTraversal(node->left, result);
    result->push(node->data);
    if (node->right)
      infixTraversal(node->right, result);
  }

  void prefixTraversal(DLNode<T> *node, queue<T> *result) {
    result->push(node->data);
    if (node->left)
      prefixTraversal(node->left, result);
    if (node->right)
      prefixTraversal(node->right, result);
  }

  void postfixTraversal(DLNode<T> *node, queue<T> *result) {
    if (node->left)
      postfixTraversal(node->left, result);
    if (node->right)
      postfixTraversal(node->right, result);
    result->push(node->data);
  }

  void findPath(DLNode<T> *node, T data) {
    if (data < node->data) {
      if (node->left)
        findPath(node->left, data);
      else {
        node->left = new DLNode<T>(data);
        count++;
      }
    } else if (data > node->data) {
      if (node->right)
        findPath(node->right, data);
      else {
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

  ~BSTree() { empty(); }

  void empty() {
    while (count) {
      remove(root->data);
    }
  }

  void add(T data) {
    if (root) {
      findPath(root, data);
    } else {
      root = new DLNode<T>(data);
      count++;
    }
  }

  queue<T> *traversal(Traversal type) {
    queue<T> *result = new queue<T>();
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
      case Breathfirst:
        break;
      }
    return result;
  }

  void remove(T data) {
    if (!root)
      return;

    enum Path { Left, Right, Root };
    DLNode<T> *leaf = root;
    DLNode<T> *parent = root;
    bool found = false;
    Path side;

    while (!found) {
      if (data < parent->data) {
        if (!parent->left)
          return;
        if (parent->left->data == data) {
          side = Left;
          leaf = parent->left;
          found = true;
        } else
          parent = parent->left;
      } else if (data > parent->data) {
        if (!parent->right)
          return;
        if (parent->right->data == data) {
          side = Right;
          leaf = parent->right;
          found = true;
        } else
          parent = parent->right;
      } else {
        side = Root;
        found = true;
        leaf = root;
      }
    }
    if (leaf->left && leaf->right) {
      DLNode<T> *tempParent = leaf->left;
      while (tempParent->right && tempParent->right->right) {
        tempParent = tempParent->right;
      }
      if (tempParent->right) {
        leaf->data = tempParent->right->data;
        if (tempParent->right->left) {
          DLNode<T> *toDelete = tempParent->right;
          tempParent->right = tempParent->right->left;
          delete toDelete;
        } else {
          delete tempParent->right;
          tempParent->right = nullptr;
        }
      } else {
        leaf->data = tempParent->data;
        leaf->left = tempParent->left;
        delete tempParent;
      }
    } else {
      switch (side) {
      case Left:
        if (!leaf->left && !leaf->right) {
          parent->left = nullptr;
        } else {
          parent->left = leaf->left ? leaf->left : leaf->right;
        }
        delete leaf;
        break;

      case Right:
        if (!leaf->left && !leaf->right) {
          parent->right = nullptr;
        } else {
          parent->right = leaf->left ? leaf->left : leaf->right;
        }
        delete leaf;
        break;

      case Root:
        if (!root->left && !root->right) {
          delete root;
          root = nullptr;
        } else {
          DLNode<T> *toDelete = root;
          if (root->left) {
            root = root->left;
          } else {
            root = root->right;
          }
          delete toDelete;
        }
        break;
      }
    }
    count--;
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

  size_t size() { return count; }
  T top() { return root ? root->data : NULL; }
};
