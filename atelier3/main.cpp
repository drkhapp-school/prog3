#include "ArrayQueue.hpp"
#include "ArrayStack.hpp"
#include <cctype>
#include <iostream>
#include <string>

using namespace std;

// Défini la priorité des operations.
int getPriority(char expression) {
  switch (expression) {
  case '+':
  case '-':
    return 1;
  case '%':
  case '/':
  case 'x':
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
  ArrayQueue<string> *queuePostfix =
      new ArrayQueue<string>(expressionQueue->getCount());
  ArrayStack<char> *stackOperators =
      new ArrayStack<char>(expressionQueue->getCount());

  while (expressionQueue->getCount()) {
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
    case 'x':
    case '*':
      while (stackOperators->getSize() > 0 &&
             getPriority(stackOperators->getTop()) >=
                 getPriority(expression[0])) {
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

  delete expressionQueue;

  while (stackOperators->getSize()) {
    queuePostfix->push(string(1, stackOperators->getTop()));
    cout << stackOperators->getTop();
    stackOperators->pop();
  }

  delete stackOperators;
  return queuePostfix;
}

///\brief Calcul du résultat d'un expression postfixe.
///\param postfixQueue File contenant les opérandes et des opérateurs de
/// l'expression postfixe. \return Résultat de l'expression postfixe.
int postfixToResult(ArrayQueue<string> *postfixQueue) {
  // TODO: Implémentation ...
  int reponse;
  ArrayStack<int> *stackOperand = new ArrayStack<int>(postfixQueue->getCount());

  while (postfixQueue->getCount()) {
    string expression = postfixQueue->getFront();
    postfixQueue->pop();

    if (isdigit(expression[0])) {
      stackOperand->push(stoi(expression));
    } else {
      int secondOp = stackOperand->getTop();
      stackOperand->pop();
      int firstOp = stackOperand->getTop();
      stackOperand->pop();

      switch (expression[0]) {
      case '+':
        stackOperand->push(firstOp + secondOp);
        break;
      case '-':
        stackOperand->push(firstOp - secondOp);
        break;
      case 'x':
      case '*':
        stackOperand->push(firstOp * secondOp);
        break;
      case '/':
        stackOperand->push(firstOp / secondOp);
        break;
      case '%':
        stackOperand->push(firstOp % secondOp);
        break;
      }
    }
  }

  delete postfixQueue;
  reponse = stackOperand->getTop();
  delete stackOperand;

  return reponse;
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
    case 'x':
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
