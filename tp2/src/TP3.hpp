/**
 * @file TP3.hpp
 * @brief Classeur de dossier et de fichiers.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-11-25
 */
#include "BSTree.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
//#include "AVLTree"
#include "Folder.hpp"
#include "Window.hpp"

using namespace std;

inline Stack<Folder *> *path;
inline BSTree<int> *selections;

inline void drawItem(Icon icon, string name, int x, int y,
                     bool selected = false) {
  if (Window::getStringWidth(name) >= Window::getIconWidth()) {
    name.resize(14);
    name.replace(name.end(), name.end() - 3, "...");
  }
  Window::drawIcon(icon, x, y, selected);
  Window::drawString(
      name, (Window::getIconWidth() - Window::getStringWidth(name)) / 2 + x,
      y + (Window::getIconHeight() * 0.75));
}

/**
 * @brief Obtention de l'indice de l'élément clické
 *
 * @param x Position de la souris, en pixels, sur l'axe des x
 * @param y Position de la souris, en pixels, sur l'axe des y
 * @return Indice de l'élément
 */
inline int getIndex(const int &x, const int &y) {
  // TODO : Retourner l'indice de l'élément clické
  int columns = Window::getWidth() / Window::getIconWidth();

  return (x / Window::getIconWidth() + (y / Window::getIconHeight() * columns));
}

/**
 * @brief Automatiquement appelée lorsque la fenêtre s'ouvre
 */
inline void onInit() {
  // TODO : Initialisations
  Folder *root = new Folder("owo");
  selections = new BSTree<int>;
  path = new Stack<Folder *>();
  path->push(root);

  root->createFolder(new Folder("hiii"));
  root->createFolder(new Folder("epic files"));
  root->createFolder(new Folder("an interesting name"));
  root->createNote(new Note("cute note"));
  root->createNote(new Note("ok note"));
  root->createNote(new Note("secret note"));
  root->createNote(new Note("interesting note"));
  root->createNote(new Note("meh note"));
  root->createNote(new Note("ugly note"));
  root->createNote(new Note("a note"));
  root->createNote(new Note("note"));
  root->createNote(new Note("?? note"));
  root->createNote(new Note("note..."));
  root->createNote(new Note("note! >.<"));
  root->createNote(new Note("extremelylongnamebecauseitisabsolutegarbage"));
  Window::setTitle(path->top()->getName());
}

/**
 * @brief Automatiquement appelée environ 60 fois par seconde
 */
inline void onRefresh() {
  // TODO : Afficher le contenu du dossier actuel
  // Get the current folder's contents
  int x = 0;
  int y = 0;

  // Go back to previous
  if (path->top()->getName() != "/") {
    drawItem(Icon::FOLDER, "..", 0, 0, selections->search(-1));
    x += Window::getIconWidth();
  }

  // All folders
  for (int i = 0; i < path->top()->getFoldersCount(); i++) {
    if (x + Window::getIconWidth() > Window::getWidth()) {
      y += Window::getIconHeight();
      x = 0;
    }
    drawItem(Icon::FOLDER, path->top()->getChildFolderName(i), x, y,
             selections->search(i));
    x += Window::getIconWidth();
  }

  // All notes
  for (int i = 0; i < path->top()->getNotesCount(); i++) {
    if (x + Window::getIconWidth() > Window::getWidth()) {
      y += Window::getIconHeight();
      x = 0;
    }
    drawItem(Icon::NOTE, path->top()->getChildNoteName(i), x, y,
             selections->search(path->top()->getFoldersCount() + i));
    x += Window::getIconWidth();
  }
}

/**
 * @brief Automatiquement appelée lors d'un click de souris dans la fenêtre
 *
 * @param x Position, en pixels, sur l'axe des x
 * @param y Position, en pixels, sur l'axe des y
 * @param button Bouton clické 
 * @param ctrl Si la touche "Ctrl" est enfoncée
 */
inline void onWindowClick(const int &x, const int &y, const bool &button,
                          const bool &ctrl) {
  if (button) {
    // TODO : Click sur un dossier ou une note du dossier actuel
    int index = getIndex(x, y);

    if (path->top()->getName() != "/")
      index--;

    if (ctrl) {
      if (index <= path->top()->getSize() && index >= 0) {
        if (selections->search(index)) {
          selections->remove(index);
        } else {
          selections->add(index);
        }
      }
    } else {
      selections->empty();
      if (index <= path->top()->getSize())
        selections->add(index);
    }
  } else {
    // TODO : Afficher le menu
    Window::showMenu(x, y, Menu::NEW_FOLDER | Menu::NEW_NOTE);
  }
}

/**
 * @brief Automatiquement appelée lors d'un click de souris dans le menu 
 * contextuel
 * @param menu Élément de menu clické
 *
 */
inline void onMenuClick(const unsigned int &menuItem) {
  switch (menuItem) {
  case Menu::NEW_FOLDER: {
    // TODO : Créer un nouveau dossier dans le dossier actuel
    string name = Window::showTextField();
    path->top()->createFolder(new Folder(name));
    break;
  }
  case Menu::NEW_NOTE: {
    string name = Window::showTextField();
    path->top()->createNote(new Note(name));
    break;
  }
  case Menu::RENAME:
    // TODO : Renommer le dossier ou la note
    break;

  case Menu::DELETE:
    // TODO : Supprimer le ou les dossiers, et tout ce qu'ils contiennent, et
    // les notes sélectionnés
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

/**
 * @brief Automatiquement appelée lorsque la fenêtre se ferme
 */
inline void onQuit() {
  // TODO : Libération
  while (path->size()) {
    delete path->top();
    path->pop();
  }
  delete path;
  delete selections;
}
