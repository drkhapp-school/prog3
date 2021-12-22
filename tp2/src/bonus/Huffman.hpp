#include "../DLNode.hpp"
#include "PriorityQueue.hpp"
#include <string>
#include <algorithm>

using std::string;

/**
 * @brief Génération de l'arbre Huffman
 * @return Un arbre Huffman
 */
inline DLNode<char>* generateTree() {
    PriorityQueue<DLNode<char> *> *key = new PriorityQueue<DLNode<char> *>;
    string content = "lol";

    while (content.length()) {
        char c = content[0];

        int value = 0;
        for (int i = 0; i < content.size(); i++ ) {
            if (content[i] ==c)
                value ++;
        }


        key->push(new DLNode<char>(c), value);
        content.erase(remove(content.begin(), content.end(), c), content.end());
    }

    DLNode<char> *tree;
    while (key->size()) {
        DLNode<char> *node = new DLNode<char>('\0');
        size_t priority = 0;

        node->left = key->front_data();
        priority += key->front_priority();
        key->pop();

        node->right = key->front_data();
        priority += key->front_priority();
        key->pop();

        if (key->size() > 1) {
            key->push(node, priority);
        } else {
            tree = node;
        }
    }

    key->pop();
    delete key;

    return tree;
}

inline string encode(string content) {
    generateTree();
    return "";
}

inline string decode() { return ""; }
