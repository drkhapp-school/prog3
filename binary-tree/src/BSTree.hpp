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

  ~BSTree() {}

  void add(T data) {
    if (!root) {
      root = new DLNode<T>(data);
      count++;
      return;
    }

    DLNode<T> *runner = root;
    while (runner) {
      if (data < runner->data) {
        if (runner->left)
          runner = runner->left;
        else {
          runner->left = new DLNode<T>(data);
          runner = nullptr;
        }
      } else if (data > runner->data) {
        if (runner->right)
          runner = runner->right;
        else {
          runner->right = new DLNode<T>(data);
          runner = nullptr;
        }
      } else {
        return;
      }
    }
    count++;
  }

  void recursiveAdd(T data) {
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
    if (!root) return;
    enum Direction { Left, Right, Root };
    DLNode<T> *parent = root;
    bool found = false;
    Direction childSide;
    while (!found) {
      if (data < parent->data) {
        if (!parent->left)
          return;
        if (parent->left->data == data) {
          found = true;
          childSide = Left;
        } else
          parent = parent->left;
      } else if (data > parent->data) {
        if (!parent->right)
          return;
        if (parent->right->data == data) {
          found = true;
          childSide = Right;
        } else
          parent = parent->right;
      } else {
        found = true;
        childSide = Root;
      }
    }

    DLNode<T> *leaf;
    if (childSide == Root) {
      if (root->left) {
        DLNode<T> *tempParent = root->left;
        while (tempParent->right && tempParent->right->right) {
          tempParent = tempParent->right;
        }
        if (tempParent->right) {
          root->data = tempParent->right->data;
          delete tempParent->right;
          tempParent->right = nullptr;
        } else {
          root->data = tempParent->data;
          root->left = tempParent->left;
        }
      } else if (root->right) {
        DLNode<T> *tempParent = root->right;
        while (tempParent->left && tempParent->left->left) {
          tempParent = tempParent->left;
        }
        if (tempParent->left) {
          root->data = tempParent->left->data;
          delete tempParent->left;
          tempParent->left = nullptr;
        } else {
          root->data = tempParent->data;
          root->left = tempParent->left;
        }
      } else {
        delete root;
        root = nullptr;
      }
    } else {
      leaf = childSide == Left ? parent->left : parent->right;
      if (!leaf->left && !leaf->right) {
        (childSide == Left) ? parent->left = nullptr : parent->right = nullptr;
        delete leaf;
      } else if (leaf->left && leaf->right) {
        DLNode<T> *tempParent = leaf->left;
        while (tempParent->right && tempParent->right->right) {
          tempParent = tempParent->right;
        }
        if (tempParent->right) {
          leaf->data = tempParent->right->data;
          delete tempParent->right;
          tempParent->right = nullptr;
        } else {
          leaf->data = tempParent->data;
          leaf->left = tempParent->left;
        }
      } else {
        if (leaf->left) {
          parent->left = leaf->left;
          (childSide == Left) ? parent->left = leaf->left
                              : parent->right = leaf->left;
          delete leaf;
        } else {
          parent->left = leaf->right;
          (childSide == Left) ? parent->left = leaf->right
                              : parent->right = leaf->right;
          delete leaf;
        }
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
};
