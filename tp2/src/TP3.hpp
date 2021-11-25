 /**
 * @file TP3.hpp
 * @brief Classeur de dossier et de fichiers. 
 * @author 1927230 - Jean-Philippe 
 * @version 1.0.0
 * @date 2021-11-25
 */
#include "Stack.hpp"
#include "Queue.hpp" 
#include "BSTree.hpp"
//#include "AVLTree"
#include "Folder.hpp"
#include "Window.hpp"

using namespace std;

inline Folder *root;
inline Stack<Folder *> *path;
// AVLTree<int>* selections;

/** 
 * @brief Obtention de l'indice de l'�l�ment click�
 *
 * @param x Position de la souris, en pixels, sur l'axe des x
 * @param y Position de la souris, en pixels, sur l'axe des y
 * @return Indice de l'�l�ment
 */
inline int getIndex(const int &x, const int &y) {
  // TODO : Retourner l'indice de l'�l�ment click�
  return -1;
}

/**
 * @brief Automatiquement appel�e lorsque la fen�tre s'ouvre
 */
inline void onInit() {
  // TODO : Initialisations
}

/**
 * @brief Automatiquement appel�e environ 60 fois par seconde
 */
inline void onRefresh() {
  // TODO : Afficher le contenu du dossier actuel
  Window::drawIcon(Icon::FOLDER, 0, 0);
  Window::drawString("really sussy folder", 0, Window::getIconHeight());
  Window::drawIcon(Icon::FOLDER, Window::getIconWidth(), 0);
  Window::drawString("folder two >.<", Window::getIconWidth(),
                     Window::getIconHeight());
  Window::drawIcon(Icon::NOTE, Window::getIconWidth() * 2, 0);
  Window::drawString("notes.txt", Window::getIconWidth() * 2,
                     Window::getIconHeight());
}

/**
 * @brief Automatiquement appel�e lors d'un click de souris dans la fen�tre
 *
 * @param x Position, en pixels, sur l'axe des x
 * @param y Position, en pixels, sur l'axe des y
 * @param button Bouton click� 
 * @param ctrl Si la touche "Ctrl" est enfonc�e
 */
inline void onWindowClick(const int &x, const int &y, const bool &button,
                          const bool &ctrl) {
  if (button) {
    // TODO : Click sur un dossier ou une note du dossier actuel
  } else {
    // TODO : Afficher le menu
  }
}

/**
 * @brief Automatiquement appel�e lors d'un click de souris dans le menu 
 * contextuel
 * @param menu �l�ment de menu click�
 *
 */
inline void onMenuClick(const unsigned int &menuItem) {
  switch (menuItem) {
  case Menu::NEW_FOLDER:
    // TODO : Cr�er un nouveau dossier dans le dossier actuel
    break;

  case Menu::NEW_NOTE:
    // TODO : Cr�er une nouvelle note dans le dossier actuel
    break;

  case Menu::RENAME:
    // TODO : Renommer le dossier ou la note
    break;

  case Menu::DELETE:
    // TODO : Supprimer le ou les dossiers, et tout ce qu'ils contiennent, et
    // les notes s�lectionn�s
    break;

  case Menu::ENCODE:
    // TODO : Encoder la note avec la m�thode de Huffman
    break;

  case Menu::DECODE:
    // TODO : D�coder la note avec la m�thode de Huffman
    break;

  case Menu::SELECT_ALL:
    // TODO : S�lectionner tous les dossiers et notes du dossier actuel
    break;
  }
}

/**
 * @brief Automatiquement appel�e lorsque la fen�tre se ferme
 */
inline void onQuit() {
  // TODO : Lib�rations
}
