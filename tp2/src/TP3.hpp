#include <queue>
#include <stack>
//#include "BSTree.hpp"
//#include "AVLTree"
#include "Window.hpp"
#include "Folder.hpp"

using namespace std;

inline Folder *root;
inline stack<Folder *> *path;
// AVLTree<int>* selections;

inline int getIndex(const int &x, const int &y) {
  // TODO : Retourner l'indice de l'élément clické
  return -1;
}

inline void onInit() {
  // TODO : Initialisations
    Window::drawIcon(Icon::NOTE, 0, 0);
    Window::drawString("yo whats good", 0, 0);
}

inline void onRefresh() {
  // TODO : Afficher le contenu du dossier actuel
}

inline void onWindowClick(const int &x, const int &y, const bool &button,
                   const bool &ctrl) {
  if (button) {
    // TODO : Click sur un dossier ou une note du dossier actuel
  } else {
    // TODO : Afficher le menu
  }
}

inline void onMenuClick(const unsigned int &menuItem) {
  switch (menuItem) {
  case Menu::NEW_FOLDER:
    // TODO : Créer un nouveau dossier dans le dossier actuel
    break;

  case Menu::NEW_NOTE:
    // TODO : Créer une nouvelle note dans le dossier actuel
    break;

  case Menu::RENAME:
    // TODO : Renommer le dossier ou la note
    break;

  case Menu::DELETE:
    // TODO : Supprimer le ou les dossiers, et tout ce qu'ils contiennent, et la
    // ou les notes sélectionnés
    break;

  case Menu::ENCODE:
    // TODO : Encoder la note avec la méthode de Huffman
    break;

  case Menu::DECODE:
    // TODO : Décoder la note avec la méthode de Huffman
    break;

  case Menu::SELECT_ALL:
    // TODO : Sélectionner tous les dossiers et notes du dossier actuel
    break;
  }
}

inline void onQuit() {
  // TODO : Libérations
}
