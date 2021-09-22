#include <stdio.h>

#define MAX 10

int stack[MAX];
int topIndex = 0;

void push(int k) {
  if (topIndex < MAX)
    stack[topIndex++] = k;
}

void pop() {
  if (topIndex)
    topIndex--;
}

int top() {
  return topIndex ? stack[topIndex - 1] : NULL;
}

int size() {
  return topIndex;
}

void printTop() {
  printf("Top is: %i\n", top());
}

void printSize() {
  printf("Size is: %i\n", size());
}

void printPile() {
  printf("Current pile is at: ");
  for (int i = 0; i < topIndex; i++)
    printf("%i, ", stack[i]);

  printf("\n");
}
