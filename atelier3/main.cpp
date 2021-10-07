#include "ArrayQueue.hpp"
#include "ArrayStack.hpp"
#include <iostream>
#include <string>

using namespace std;

///\brief Transformation d'une expression infixe en expression postfixe.
///\param expressionQueue File contenant les opérandes et des opérateurs de
/// l'expression infixe. \return File de l'expression postfixe.
ArrayQueue<string> *infixToPostfix(ArrayQueue<string> *expressionQueue) {
  // TODO : Implémentation ...
}

///\brief Calcul du résultat d'un expression postfixe.
///\param postfixQueue File contenant les opérandes et des opérateurs de
/// l'expression postfixe. \return Résultat de l'expression postfixe.
int postfixToResult(ArrayQueue<string> *postfixQueue) {
  // TODO: Implémentation ...
}

///\brief Fonction principale.
///\return Code de terminaison de programme.
int main(int argc, char **argv) {
  int size;
  string infix;

  if (!argv[1]) {
    cout << "Quel est l'opération? ";
    getline(cin, infix);
  } else {
    infix = argv[1];
    infix.erase(remove(infix.begin(), infix.end(), '"'), infix.end());
  }

  size = infix.length();
  ArrayQueue<string> fileInfix(size);

  // TODO : Enfilement des opérandes et des opérateurs de l'expression infixe.
  for (string::size_type i = 0; i < size; i++) {
    string input;
    // parse int
    for (int buffer = 0; isdigit(infix[i]) && i < size; buffer++)
      input += infix[i++];

    fileInfix.push(input);

    // parse operator
    switch (infix[i]) {
    case '+':
    case '-':
    case '*':
    case 'x':
    case '/':
    case '(':
    case ')':
      fileInfix.push(to_string(infix[i]));
      break;
    case '\0':
    case ' ':
      break;
    default:
      cout << "Invalid input. '" << infix[i] << "'" << endl
           << "Please only use digits 0 to 9, and the symbols + - * x / "
              "( ) %."
           << endl;
      return 1;
    }
  }

  // TODO : Appel des fonction pour transformer l'expression et calculer le
  // résultat.
  ArrayQueue<string> *filePostfix = infixToPostfix(&fileInfix);

  return 0;
}
