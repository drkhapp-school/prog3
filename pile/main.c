#include <stdio.h>
#include <stdlib.h>
#include "ArrayStack.h"

int main() {
    struct ArrayStack stackA;

    init(&stackA);
    push(&stackA, 42);

    printf("Pile A -> Dessus: %i, compte: %i\n", top(&stackA), size(&stackA));
    struct ArrayStack stackB;

    init(&stackB);
    push(&stackB, 200);

    printf("Pile B -> Dessus: %i, compte: %i\n", top(&stackB), size(&stackB));
    return 0;
}
