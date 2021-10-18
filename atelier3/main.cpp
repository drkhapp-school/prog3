/**
 * @file main.cpp
 * @brief Évaluation d'une expression mathématique en respectant la priorité des op
 * rateurs.
 * @author Jean-Philippe Miguel-Gagnon
 * @version v1.0.0
 * @date 2021-10-18
 */
#include "ArrayQueue.hpp"
#include "ArrayStack.hpp"
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Détermine si une expression est un chiffre.
 * @param expression Le expression à tester.
 * @return Vrai si c'est un chiffre, sinon faux.
 */
bool isDigit(char expression) {
  switch (expression) {
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    return true;
  default:
    return false;
  }
}

/**
 * @brief Détermine si une expression est un opérateur valid.
 * @param expression L'expression à tester.
 * @return Vrai si c'est un opérateur valid, sinon faux.
 */
bool isOperator(string expression) {
  switch (expression[0]) {
  case '(':
  case ')':
  case '+':
  case '-':
  case '%':
  case '/':
  case 'x':
  case '*':
    return true;
  default:
    return false;
  }
}

/**
 * @brief Détermine la priorité de l'expression.
 * @param expression L'expression à tester.
 * @return La priorité de l'expression.
 */
unsigned char getPriority(string expression) {
  switch (expression[0]) {
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

/**
 * @brief Transformation d'une entrée de l'utilisateur en expression infixe.
 * @param input String contenant l'entrée de l'utilisateur.
 * @return File de l'expression postfixe.
 */
ArrayQueue<string> *inputToInfix(string input) {
  ArrayQueue<string> *fileInfix = new ArrayQueue<string>(input.length());
  for (string::size_type i = 0; i < input.length(); i++) {
    // Vérification des nombres
    if (isDigit(input[i])) {
      string buffer;
      while (isDigit(input[i]) && i < input.length())
        buffer += input[i++];

      fileInfix->push(buffer);
      cout << buffer;
    }
    // Vérfiication de l'operateur
    if (isOperator(string(1, input[i]))) {
      fileInfix->push(string(1, input[i]));
      cout << string(1, input[i]);
    }
  }
  return fileInfix;
}

/**
 * @brief Transformation d'une expression infixe en expression postfixe.
 * @param expressionQueue File contenant les opérandes et des opérateurs de l
 * expression infixe.
 * @return File de l'expression postfixe.
 */
ArrayQueue<string> *infixToPostfix(ArrayQueue<string> *expressionQueue) {
  int size = expressionQueue->getCount();
  ArrayQueue<string> *queuePostfix = new ArrayQueue<string>(size);
  ArrayStack<string> *stackOperators = new ArrayStack<string>(size);

  while (expressionQueue->getCount()) {
    string expression = expressionQueue->getFront();
    expressionQueue->pop();

    if (isOperator(expression)) {
      switch (expression[0]) {
      case '(':
        stackOperators->push(expression);
        break;
      case ')':
        while (stackOperators->getSize() > 0 &&
               stackOperators->getTop() != "(") {
          queuePostfix->push(stackOperators->getTop());
          cout << stackOperators->getTop();
          stackOperators->pop();
        }

        if (stackOperators->getSize() == 0) {
          cerr << endl << endl << "Paranthèse ouvrante manquante." << endl;
          exit(1);
        }

        stackOperators->pop();
        break;
      default:
        while (stackOperators->getSize() > 0 &&
               getPriority(stackOperators->getTop()) >=
                   getPriority(expression)) {
          queuePostfix->push(stackOperators->getTop());
          cout << stackOperators->getTop();
          stackOperators->pop();
        }
        stackOperators->push(expression);
        break;
      }
    }
    // Nombres
    else {
      queuePostfix->push(expression);
      cout << expression;
    }
  }

  delete expressionQueue;

  while (stackOperators->getSize()) {
    if (stackOperators->getTop() != "(") {
      queuePostfix->push(stackOperators->getTop());
      cout << stackOperators->getTop();
    }
    stackOperators->pop();
  }

  delete stackOperators;
  return queuePostfix;
}

/**
 * @brief Calcul du résultat d'un expression postfixe.
 * @param postfixQueue File contenant les opérandes et des opérateurs de
 * l'expression postfixe.
 * @return Résultat de l'expression postfixe.
 */
int postfixToResult(ArrayQueue<string> *postfixQueue) {
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

  int reponse;
  reponse = stackOperand->getTop();
  delete stackOperand;

  return reponse;
}

/**
 * @brief Fonction principale.
 * @return Code de terminaison de programme.
 */
int main(int argc, char **argv) {
  string input;

  if (argv[1]) {
    input = argv[1];
    input.erase(remove(input.begin(), input.end(), '"'), input.end());
  } else {
    cout << "Quel est l'opération? ";
    getline(cin, input);
  }

  ArrayQueue<string> *fileInfix;
  cout << "Infix: ";
  fileInfix = inputToInfix(input);
  cout << endl;

  ArrayQueue<string> *filePostfix;
  cout << "Postfix: ";
  filePostfix = infixToPostfix(fileInfix);
  cout << endl;

  int reponse = postfixToResult(filePostfix);
  cout << "Réponse: " << reponse << endl;

  return 0;
}
