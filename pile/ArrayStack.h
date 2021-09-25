#include <stdio.h>

#define MAX 10

struct ArrayStack {
  int array[MAX];
  int topIndex;
};

// Initializer la pile
void init(struct ArrayStack *stack) { stack->topIndex = 0; }

// Envoyer un donné dans la pile
void push(struct ArrayStack *stack, int k) {
  if (stack->topIndex < MAX)
    stack->array[stack->topIndex++] = k;
}

// Enlever un donné de la pile
void pop(struct ArrayStack *stack) {
  if (stack->topIndex)
    stack->topIndex--;
}

// Donner la valeur du dessus de la pile
int top(struct ArrayStack *stack) {
  return stack->topIndex ? stack->array[stack->topIndex - 1] : 0;
}

// Donner la valeur au dessus de la pile
int size(struct ArrayStack *stack) { return stack->topIndex; }
