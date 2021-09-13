# Atelier 2

## Que se passe-t-il suite à l'exécution de la ligne 1?
On fait une operation XOR sur la valeur RXA par RXA, ce qui l'initialize à 0 (toute opération xor sur lui-même donne 0).

## Quel registre est affecté peu importe l'instruction exécutée et pourquoi?
RIP, ce registre est liée au pointeur d'instruction.

## Quel autre registre est affecté suite à l'instruction de la ligne 2?
RSP, ce registre est liée au pointeur de stack.

## Est-ce que le résultat de l'instruction à la ligne 5 est valide et comment pouvons-nous nous en assurer?
Non, car 7D + 87 doit donner 104, mais on a seulement 4. On peut le constater avec les flags.

## Que se passe-t-il avec les valeurs des registres BX et CX suite aux instructions 11, 12, 13 et 14 et pourquoi?
Les valeurs BX et CX s'inverse, car on
- insère BX
- insère CX
- enlève la valeur sur le dessus (qui est CX) et on le mets dans BX
- enlève la valeur (qui est BX) et on le mets dans CX

## Quel registre est affecté à notre insu lors de l'exécution de l'instruction à la ligne 8?
RSP, on met un pointeur pour dire où on était dans la fonction.

## Quelle est la principale utilité de la pile des programmes exécutés en mémoire centrale?
Elle est utilisé pour les méthodes, quand on appelle une méthode on push la valeur de RIP, et lorsqu'on a fini avec la méthode, on pop la ligne d'instruction dans RIP.
