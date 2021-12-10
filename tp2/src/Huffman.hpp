#include "DLNode.hpp"
#include "PriorityQueue.hpp"
#include <iostream>
#include <string>

using std::string;
inline string encode(string content) {
  // Generate key
  PriorityQueue<DLNode<char> *> *key = new PriorityQueue<DLNode<char> *>;

  while (content.length()) {
    char c = content[0];

    // Get character occurences
    int value = 0;
    for (int j = 0; j < content.length(); j++)
      if (content[j] == c)
        value++;

    key->push(new DLNode<char>(c), value);
    content.erase(remove(content.begin(), content.end(), c), content.end());
  }

  // Create tree
  while (key->size() != 1) {
    DLNode<char> *node = new DLNode<char>('\0');
    size_t priority = 0;
    node->left = key->front(); 
    priority += key->priority();
    key->pop();
    node->right = key->front(); 
    priority += key->priority();
    key->pop();
    key->push(node, priority);
  }

  return "";
}

inline string decode() { return ""; }
