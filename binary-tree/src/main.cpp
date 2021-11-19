#include "BSTree.hpp"
#include <iostream>
#include <queue>

using namespace std;

int main() {
  BSTree<int> *tree = new BSTree<int>;
  queue<int> *traversal;
  /* tree->recursiveAdd(4); */
  /* tree->recursiveAdd(6); */
  /* tree->recursiveAdd(8); */
  /* tree->recursiveAdd(2); */
  /* tree->recursiveAdd(9); */
  /* tree->recursiveAdd(10); */
  /* tree->recursiveAdd(1); */
  tree->add(42);
  tree->add(404);
  tree->add(666);
  tree->add(32);
  tree->add(69);
  tree->add(23);
  tree->add(11);
  tree->add(12);
  tree->add(21);

  tree->remove(11);

  cout << "Prefix: [";
  traversal = tree->traversal(Prefix);
  while (traversal->size()) {
    cout << traversal->front() << (traversal->size() == 1 ? "" : ", ");
    traversal->pop();
  }
  cout << "]" << endl;

  cout << "Infix: [";
  traversal = tree->traversal(Infix);
  while (traversal->size()) {
    cout << traversal->front() << (traversal->size() == 1 ? "" : ", ");
    traversal->pop();
  }
  cout << "]" << endl;

  cout << "Postfix: [";
  traversal = tree->traversal(Postfix);
  while (traversal->size()) {
    cout << traversal->front() << (traversal->size() == 1 ? "" : ", ");

    traversal->pop();
  }
  cout << "]" << endl;

  delete tree;
  delete traversal;
  return 0;
}
