#include <stdio.h>
#include <stdlib.h>

struct ArrayStack {
  int *array;
  int size;
  int topIndex; 
};

// Allocation de la pile
void create(struct ArrayStack *stack, int size) {
  stack->array = malloc(size * 8);
  stack->size = size;
  stack->topIndex = 0;
}

// Libération de la pile
void destroy(struct ArrayStack *stack) {
  free(stack->array);
}

// Envoyer un donné dans la pile
void push(struct ArrayStack *stack, int k) {
  if (stack->topIndex < stack->size)
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
