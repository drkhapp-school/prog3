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
inline int selectedIndex;

inline void drawItem(Icon icon, string name, int x, int y,
                     bool selected = false) {
  if (Window::getStringWidth(name + "...") > Window::getIconWidth()) {
    while (Window::getStringWidth(name + "...") > Window::getIconWidth()) {
      name.pop_back();
    }
    name += "...";
  }
  Window::drawIcon(icon, x, y, selected);
  Window::drawString(
      name, (Window::getIconWidth() - Window::getStringWidth(name)) / 2 + x,
      y + (Window::getIconHeight() * 0.75));
}

/**
 * @brief Obtention de l'indice de l'�l�ment click�
 *
 * @param x Position de la souris, en pixels, sur l'axe des x
 * @param y Position de la souris, en pixels, sur l'axe des y
 * @return Indice de l'�l�ment
 */
inline int getIndex(const int &x, const int &y) {
  // TODO : Retourner l'indice de l'�l�ment click�
  int columns = Window::getWidth() / Window::getIconWidth();

  return (x / Window::getIconWidth() + (y / Window::getIconHeight() * columns));
}

/**
 * @brief Automatiquement appel�e lorsque la fen�tre s'ouvre
 */
inline void onInit() {
  // TODO : Initialisations
  Folder *root = new Folder("/");
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
 * @brief Automatiquement appel�e environ 60 fois par seconde
 */
inline void onRefresh() {
  // TODO : Afficher le contenu du dossier actuel
  // Get the current folder's contents
  int x = 0;
  int y = 0;

  // Go back to previous
  if (path->size() > 1) {
    drawItem(Icon::FOLDER, "..", 0, 0, selections->search(-1));
    x += Window::getIconWidth();
  }

  // All folders
  for (int i = 0; i < path->top()->getFoldersCount(); i++) {
    if (x + Window::getIconWidth() > Window::getWidth()) {
      y += Window::getIconHeight();
      x = 0;
    }
    drawItem(Icon::FOLDER, path->top()->getChildFolder(i)->getName(), x, y,
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
 * @brief Automatiquement appel�e lors d'un click de souris dans la fen�tre
 *
 * @param x Position, en pixels, sur l'axe des x
 * @param y Position, en pixels, sur l'axe des y
 * @param button Bouton click� 
 * @param ctrl Si la touche "Ctrl" est enfonc�e
 */
inline void onWindowClick(const int &x, const int &y, const bool &button,
                          const bool &ctrl) {
  int index = getIndex(x, y);
  if (path->size() > 1)
    index--;

  if (button) {
    // TODO : Click sur un dossier ou une note du dossier actuel
    if (ctrl) {
      if (index <= path->top()->getSize() && index >= 0) {
        if (selections->search(index)) {
          selections->remove(index);
        } else {
          selections->add(index);
        }
      }
    } else {
      if (selections->search(index)) {
        selections->empty();
        if (index == -1) {
          path->pop();
        } else if (index < path->top()->getFoldersCount()) {
          path->push(path->top()->getChildFolder(index));
        }
        Window::setTitle(path->top()->getName());
      } else {
        selections->empty();
        if (index <= path->top()->getSize())
          selections->add(index);
      }
    }
  } else {
    // TODO : Afficher le menu
    if (index >= path->top()->getSize()) {
      Window::showMenu(x, y,
                       Menu::NEW_FOLDER | Menu::NEW_NOTE | Menu::SELECT_ALL);
    } else {
      if (!selections->search(index)) {
        if (!ctrl) {
          selections->empty();
        }
        selections->add(index);
      }
      if (index != -1) {
        selectedIndex = index;
        if (index < path->top()->getFoldersCount()) {
          Window::showMenu(x, y, Menu::RENAME | Menu::DELETE);
        } else {
          Window::showMenu(x, y, Menu::ENCODE | Menu::DELETE | Menu::RENAME);
        }
      }
    }
  }
}

/**
 * @brief Automatiquement appel�e lors d'un click de souris dans le menu 
 * contextuel
 * @param menu �l�ment de menu click�
 */
inline void onMenuClick(const unsigned int &menuItem) {
  switch (menuItem) {
  case Menu::NEW_FOLDER: {
    // TODO : Cr�er un nouveau dossier dans le dossier actuel
    string name = Window::showTextField();
    if (name != "")
      path->top()->createFolder(new Folder(name));
    break;
  }
  case Menu::NEW_NOTE: {
    string name = Window::showTextField();
    if (name != "")
      path->top()->createNote(new Note(name));
    break;
  }
  case Menu::RENAME: {
    // TODO : Renommer le dossier ou la note
    if (selectedIndex < path->top()->getFoldersCount()) {
      string name =
          Window::showTextField(path->top()->getChildFolderName(selectedIndex));
      if (name != "")
        path->top()->renameChildFolder(selectedIndex, name);
    } else {
      selectedIndex -= path->top()->getFoldersCount();
      string name =
          Window::showTextField(path->top()->getChildNoteName(selectedIndex));
      if (name != "")
        path->top()->renameChildNote(selectedIndex, name);
    }
    selections->empty();
    break;
  }
  case Menu::DELETE:
    // TODO : Supprimer le ou les dossiers, et tout ce qu'ils contiennent, et
    // les notes s�lectionn�s
    /* if (selectedIndex < path->top()->getFoldersCount()) { */
    /*   path->top()->deleteChildFolder(selectedIndex); */
    /* } else { */
    /*   string name = Window::showTextField(); */
    /*   path->top()->deleteChildNote(selectedIndex/); */
    /* } */
    /* selections->empty(); */
    break;

  case Menu::ENCODE:
    // TODO : Encoder la note avec la m�thode de Huffman
    break;

  case Menu::DECODE:
    // TODO : D�coder la note avec la m�thode de Huffman
    break;

  case Menu::SELECT_ALL:
    for (int i = 0; i < path->top()->getSize(); i++) {
      selections->add(i);
    };
    break;
  }
}

/**
 * @brief Automatiquement appel�e lorsque la fen�tre se ferme
 */
inline void onQuit() {
  // TODO : Lib�ration
  while (path->size()) {
    delete path->top();
    path->pop();
  }
  delete path;
  delete selections;
}
