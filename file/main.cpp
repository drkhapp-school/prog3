#include "ArrayQueue.hpp"
#include <cstdio>

int main() {
  ArrayQueue<int> file(5);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(42);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(4);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.pop();
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(404);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(422);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(4124);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(5432);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(4012);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(404);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.pop();
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  file.push(666);
  printf("front %i back %i count %lu\n", file.getFront(), file.getBack(),
         file.getCount());
  return 0;
}
