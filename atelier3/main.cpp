#include "ArrayQueue.hpp"
#include "ArrayStack.hpp"
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

// Défini la priorité des operations.
int priority(char expression) {
  switch (expression) {
  case '+':
  case '-':
    return 1;
  case '%':
  case '/':
  case '*':
    return 2;
  default:
    return 0;
  }
}

///\brief Transformation d'une expression infixe en expression postfixe.
///\param expressionQueue File contenant les opérandes et des opérateurs de
/// l'expression infixe. \return File de l'expression postfixe.
ArrayQueue<string> *infixToPostfix(ArrayQueue<string> *expressionQueue) {
  // TODO : Implémentation ...
  int size = expressionQueue->getCount();
  ArrayQueue<string> *queuePostfix = new ArrayQueue<string>(size);
  ArrayStack<char> *stackOperators = new ArrayStack<char>(size);

  for (int i = 0; i < size; i++) {
    string expression = expressionQueue->getFront();
    expressionQueue->pop();

    switch (expression[0]) {
    case '(':
      stackOperators->push(expression[0]);
      break;
    case ')':
      while (stackOperators->getTop() != '(') {
        queuePostfix->push(string(1, stackOperators->getTop()));
        cout << stackOperators->getTop();
        stackOperators->pop();
      }
      stackOperators->pop();
      break;
    case '+':
    case '-':
    case '%':
    case '/':
    case '*':
      while (stackOperators->getSize() > 0 &&
             priority(stackOperators->getTop()) >= priority(expression[0])) {
        queuePostfix->push(string(1, stackOperators->getTop()));
        cout << stackOperators->getTop();
        stackOperators->pop();
      }
      stackOperators->push(expression[0]);
      break;
    default:
      queuePostfix->push(expression);
      cout << expression;
      break;
    }
  }

  while (stackOperators->getSize() != 0) {
    queuePostfix->push(string(1, stackOperators->getTop()));
    cout << stackOperators->getTop();
    stackOperators->pop();
  }

  return queuePostfix;
}

///\brief Calcul du résultat d'un expression postfixe.
///\param postfixQueue File contenant les opérandes et des opérateurs de
/// l'expression postfixe. \return Résultat de l'expression postfixe.
int postfixToResult(ArrayQueue<string> *postfixQueue) {
  // TODO: Implémentation ...
  return 0;
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

  // TODO : Enfilement des opérandes et des opérateurs de l'expression infixe.
  ArrayQueue<string> *fileInfix = new ArrayQueue<string>(size);

  cout << "Infix: ";
  for (string::size_type i = 0; i < size; i++) {
    // parse int
    if (isdigit(infix[i])) {
      string input;
      while (isdigit(infix[i]) && i < size)
        input += infix[i++];

      fileInfix->push(input);
      cout << input;
    }
    // parse operator
    switch (infix[i]) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '%':
      fileInfix->push(string(1, infix[i]));
      cout << string(1, infix[i]);
      break;
    case '\0':
    case ' ':
      break;
    default:
      cout << endl
           << "Invalid input. '" << infix[i] << "'" << endl
           << "Please only use digits 0 to 9, and the symbols + - * x / "
              "( ) %."
           << endl;
      return 1;
    }
  }
  cout << endl;

  // TODO : Appel des fonction pour transformer l'expression et calculer le
  // résultat.
  ArrayQueue<string> *filePostfix;

  cout << "Postfix: ";
  filePostfix = infixToPostfix(fileInfix);
  cout << endl;

  int reponse = postfixToResult(filePostfix);
  cout << "Réponse: " << reponse << endl;

  return 0;
}
