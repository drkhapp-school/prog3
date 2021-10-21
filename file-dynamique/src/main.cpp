#include "Queue.hpp"
#include <iostream>

using namespace std;

int main() {
  Queue<int> *fileDynamique = new Queue<int>();
  fileDynamique->push(42);
  fileDynamique->push(44);
  fileDynamique->pop();
  fileDynamique->push(420);

  return 0;
}
