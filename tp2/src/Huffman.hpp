#include "DLNode.hpp"
#include "PriorityQueue.hpp"
#include <iostream>
#include <map>
#include <string>

using std::string;

inline PriorityQueue<DLNode<char> *> *createKey() {
  PriorityQueue<DLNode<char> *> *tree = new PriorityQueue<DLNode<char> *>;
  string key = "Ce pangramme autodescriptif en hommage a Douglas Hofstadter, Lee Sallows, Jacques Pitrat, Nicolas Graner et Eric Angelini contient exactement dix-sept a, un b, onze c, huit d, trente-cinq e, cinq f, neuf g, six h, vingt-quatre i, deux j, un k, sept l, six m, vingt-six n, onze o, huit p, huit q, onze r, quinze s, vingt-sept t, dix-sept u, quatre v, deux w, neuf x, un y, et cinq z.";

  return tree;
}

inline string encode(string content) {
  // Generate tree
  PriorityQueue<DLNode<char> *> *tree = new PriorityQueue<DLNode<char> *>;

  while (content.length()) {
    char c = content[0];

    // Get character occurences
    int value = 0;
    for (int j = 0; j < content.length(); j++)
      if (content[j] == c)
        value++;

    tree->push(new DLNode<char>(c), value);
    content.erase(remove(content.begin(), content.end(), c), content.end());
  }

  // Create tree
  while (tree->size() != 1) {
    DLNode<char> *node = new DLNode<char>('\0');
    size_t priority = 0;
    node->left = tree->front();
    priority += tree->priority();
    tree->pop();
    node->right = tree->front();
    priority += tree->priority();
    tree->pop();
    tree->push(node, priority);
  }

  return "";
}

inline string decode() { return ""; }
