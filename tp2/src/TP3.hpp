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
inline string breadcrumb;

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
 * @brief Obtention de l'indice de l'élément clické
 *
 * @param x Position de la souris, en pixels, sur l'axe des x
 * @param y Position de la souris, en pixels, sur l'axe des y
 * @return Indice de l'élément
 */
inline int getIndex(const int &x, const int &y) {
  // TODO : Retourner l'indice de l'élément clické
  int index = x / Window::getIconWidth() +
              (y / Window::getIconHeight() * Window::getWidth() /
               Window::getIconWidth());

  if (path->size() > 1)
    index--;

  return index;
}

inline void createRandomFolders(Folder *parent, int random, int depth) {
  if (depth == 5)
    return;
  depth++;
  for (int i = 0; i < rand() % random + 5; i++) {
    parent->addFolder(new Folder(to_string((i + 1) * 20)));
    parent->addNote(new Note(to_string(i + 1)));
    createRandomFolders(parent->getChildFolder(i), random, depth);
  }
}

/**
 * @brief Automatiquement appelée lorsque la fenêtre s'ouvre
 */
inline void onInit() {
  // TODO : Initialisations
  Folder *root = new Folder("/");
  Folder *randomFolders = new Folder("Random folders");
  srand(time(0));
  createRandomFolders(randomFolders, 5, 0);
  selections = new BSTree<int>;
  path = new Stack<Folder *>();
  path->push(root);

  root->addFolder(new Folder("hiii"));
  root->addFolder(new Folder("an interesting name"));
  root->addFolder(randomFolders);
  root->addNote(new Note("cute note"));
  root->addNote(new Note("ok note"));
  root->addNote(new Note("secret note"));
  root->addNote(new Note("interesting note"));
  root->addNote(new Note("meh note"));
  root->addNote(new Note("ugly note"));
  root->addNote(new Note("a note"));
  root->addNote(new Note("note"));
  root->addNote(new Note("?? note"));
  root->addNote(new Note("note..."));
  root->addNote(new Note("note! >.<"));
  root->addNote(new Note("extremelylongnamebecauseitisabsolutegarbage"));
  breadcrumb = path->top()->getName();
  Window::setTitle(breadcrumb);
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
 * @brief Automatiquement appelée lors d'un click de souris dans la fenêtre
 *
 * @param x Position, en pixels, sur l'axe des x
 * @param y Position, en pixels, sur l'axe des y
 * @param button Bouton clické 
 * @param ctrl Si la touche "Ctrl" est enfoncée
 */
inline void onWindowClick(const int &x, const int &y, const bool &button,
                          const bool &ctrl) {
  int index = getIndex(x, y);
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
          breadcrumb.erase(breadcrumb.length() -
                           path->top()->getName().length());
          if (path->size() > 2) {
            breadcrumb.erase(breadcrumb.length() - 1);
          }
          path->pop();
          Window::setTitle(breadcrumb);
        } else if (index < path->top()->getFoldersCount()) {
          if (path->size() > 1) {
            breadcrumb.append("/");
          }
          path->push(path->top()->getChildFolder(index));
          breadcrumb.append(path->top()->getName());
          Window::setTitle(breadcrumb);
        } else if (index < path->top()->getSize()) {
          string newContent = Window::showTextField();
        }
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
 * @brief Automatiquement appelée lors d'un click de souris dans le menu 
 * contextuel
 * @param menu Élément de menu clické
 */
inline void onMenuClick(const unsigned int &menuItem) {
  switch (menuItem) {
  case Menu::NEW_FOLDER: {
    // TODO : Créer un nouveau dossier dans le dossier actuel
    string name = Window::showTextField();
    if (name != "" && !path->top()->folderExists(name))
      path->top()->addFolder(new Folder(name));
    break;
  }
  case Menu::NEW_NOTE: {
    string name = Window::showTextField();
    if (name != "" && !path->top()->noteExists(name))
      path->top()->addNote(new Note(name));
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
    // les notes sélectionnés
    /* if (selectedIndex < path->top()->getFoldersCount()) { */
    /*   path->top()->deleteChildFolder(selectedIndex); */
    /* } else { */
    /*   string name = Window::showTextField(); */
    /*   path->top()->deleteChildNote(selectedIndex/); */
    /* } */
    /* selections->empty(); */
    break;

  case Menu::ENCODE:
    // TODO : Encoder la note avec la méthode de Huffman
    break;

  case Menu::DECODE:
    // TODO : Décoder la note avec la méthode de Huffman
    break;

  case Menu::SELECT_ALL:
    for (int i = 0; i < path->top()->getSize(); i++) {
      selections->add(i);
    };
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
