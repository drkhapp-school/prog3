/**
 * @file main.cpp
 * @brief Évaluation d'une expression mathématique en respectant la priorité des op
 * rateurs.
 * @author Jean-Philippe Miguel-Gagnon
 * @version v1.0.0
 * @date 2021-10-22
 */
#include "ArrayQueue.hpp"
#include "ArrayStack.hpp"
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

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
  case '^':
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
  case '^':
    return 3;
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
  ArrayQueue<string> *infixQueue = new ArrayQueue<string>(input.length());
  for (string::size_type i = 0; i < input.length(); i++) {
    // Vérification d'opérande
    if (isdigit(input[i])) {
      string buffer;
      while (isdigit(input[i]))
        buffer += input[i++];

      infixQueue->push(buffer);
      cout << buffer;
    }
    // Vérification de l'operateur
    if (isOperator(string(1, input[i]))) {
      infixQueue->push(string(1, input[i]));
      cout << input[i];
    }
  }
  return infixQueue;
}

/**
 * @brief Transformation d'une expression infixe en expression postfixe.
 * @param expressQueue File contenant les opérandes et des opérateurs de l
 * expression infixe.
 * @return File de l'expression postfixe.
 */
ArrayQueue<string> *infixToPostfix(ArrayQueue<string> *expressQueue) {
  size_t size = expressQueue->getCount();
  ArrayQueue<string> *postfixQueue = new ArrayQueue<string>(size);
  ArrayStack<string> *operatorStack = new ArrayStack<string>(size);

  while (expressQueue->getCount()) {
    string express = expressQueue->getFront();
    expressQueue->pop();

    // Operateurs
    if (isOperator(express)) {
      switch (express[0]) {
      case '(':
        operatorStack->push(express);
        break;
      case ')':
        while (operatorStack->getSize() > 0 &&
               operatorStack->getTop() != "(") {
          postfixQueue->push(operatorStack->getTop());
          cout << operatorStack->getTop();
          operatorStack->pop();
        }

        if (operatorStack->getSize() == 0) {
          cerr << endl << endl << "Paranthèse ouvrante manquante." << endl;
          exit(1);
        }

        operatorStack->pop();
        break;
      default:
        while (operatorStack->getSize() > 0 &&
               getPriority(operatorStack->getTop()) >=
                   getPriority(express)) {
          postfixQueue->push(operatorStack->getTop());
          cout << operatorStack->getTop();
          operatorStack->pop();
        }
        operatorStack->push(express);
        break;
      }
    }
    // Opérandes
    else {
      postfixQueue->push(express);
      cout << express;
    }
  }
  delete expressQueue;

  // Opérateurs restantes
  while (operatorStack->getSize()) {
    if (operatorStack->getTop() != "(") {
      postfixQueue->push(operatorStack->getTop());
      cout << operatorStack->getTop();
    }
    operatorStack->pop();
  }
  delete operatorStack;

  return postfixQueue;
}

/**
 * @brief Calcul du résultat d'un expression postfixe.
 * @param postfixQueue File contenant les opérandes et des opérateurs de
 * l'expression postfixe.
 * @return Résultat de l'expression postfixe.
 */
size_t postfixToResult(ArrayQueue<string> *postfixQueue) {
  ArrayStack<size_t> *operStack =
      new ArrayStack<size_t>(postfixQueue->getCount());

  while (postfixQueue->getCount()) {
    string expression = postfixQueue->getFront();
    postfixQueue->pop();

    if (isdigit(expression[0])) {
      operStack->push(stoi(expression));
    } else {
      size_t secondOp = operStack->getTop();
      operStack->pop();
      size_t firstOp = operStack->getTop();
      operStack->pop();

      switch (expression[0]) {
      case '+':
        operStack->push(firstOp + secondOp);
        break;
      case '-':
        operStack->push(firstOp - secondOp);
        break;
      case 'x':
      case '*':
        operStack->push(firstOp * secondOp);
        break;
      case '/':
        operStack->push(firstOp / secondOp);
        break;
      case '%':
        operStack->push(firstOp % secondOp);
        break;
      case '^':
        operStack->push(pow(firstOp, secondOp));
      }
    }
  }
  delete postfixQueue;

  size_t reponse;
  reponse = operStack->getTop();
  delete operStack;

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
    cout << endl;
  }
  cout << "Entrée: " << input << endl;

  ArrayQueue<string> *infixQueue;
  cout << "Infix: ";
  infixQueue = inputToInfix(input);
  cout << endl;

  ArrayQueue<string> *postfixQueue;
  cout << "Postfix: ";
  postfixQueue = infixToPostfix(infixQueue);
  cout << endl;

  size_t reponse = postfixToResult(postfixQueue);
  cout << "Évaluation: " << reponse << endl;

  return 0;
}
