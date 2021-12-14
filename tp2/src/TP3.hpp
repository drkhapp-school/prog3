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

/**
 * @brief Automatiquement appelée lorsque la fenêtre s'ouvre
 */
inline void onInit() {
  // TODO : Initialisations
  Folder *root = new Folder("/");
  selections = new BSTree<int>;
  path = new Stack<Folder *>();
  path->push(root);

  root->add(new Folder("hiii"));
  root->add(new Folder("an interesting name"));
  root->add(new Folder("homework"));
  root->add(new Note("cute note"));
  root->add(new Note("ok note"));
  root->add(new Note("secret note"));
  root->add(new Note("interesting note"));
  root->add(new Note("meh note"));
  root->add(new Note("ugly note"));
  root->add(new Note("note! >.<"));
  root->add(new Note("extremelylongnamebecauseitisabsolutegarbage"));
  breadcrumb = "Viewing: " + path->top()->getName();
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
  for (int i = 0; i < path->top()->foldersSize(); i++) {
    if (x + Window::getIconWidth() > Window::getWidth()) {
      y += Window::getIconHeight();
      x = 0;
    }
    drawItem(Icon::FOLDER, path->top()->getChildFolder(i)->getName(), x, y,
             selections->search(i));
    x += Window::getIconWidth();
  }

  // All notes
  for (int i = 0; i < path->top()->notesSize(); i++) {
    if (x + Window::getIconWidth() > Window::getWidth()) {
      y += Window::getIconHeight();
      x = 0;
    }
    drawItem(Icon::NOTE, path->top()->getChildNoteName(i), x, y,
             selections->search(path->top()->foldersSize() + i));
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

  // Manipulation des fichiers
  if (button) {
    // Selectionner plusieurs fichiers
    if (ctrl) {
      if (index <= path->top()->size() && index >= 0) {
        if (selections->search(index)) {
          selections->remove(index);
        } else {
          selections->add(index);
        }
      }
    }
    // Acc�der un fichier
    else {
      selections->empty();

      // Retourner en arri�re
      if (index == -1) {
        breadcrumb.erase(breadcrumb.length() - path->top()->getName().length());
        if (path->size() > 2) {
          breadcrumb.erase(breadcrumb.length() - 1);
        }
        path->pop();
      }

      // Acc�der un dossier
      else if (index < path->top()->foldersSize()) {
        if (path->size() > 1) {
          breadcrumb.append("/");
        }
        path->push(path->top()->getChildFolder(index));
        breadcrumb.append(path->top()->getName());
      }

      // Modifier une note
      else if (index < path->top()->size()) {
        index -= path->top()->foldersSize();
        Window::setTitle("Editing " + path->top()->getChildNoteName(index));
        string content =
            Window::showTextField(path->top()->getChildNoteContent(index));
        path->top()->editChildNote(index, content);
      }

      Window::setTitle(breadcrumb);
    }
  }

  // Menu
  else {
    // Click droit dans le vide
    if (index >= path->top()->size()) {
      Window::showMenu(x, y,
                       Menu::NEW_FOLDER | Menu::NEW_NOTE | Menu::SELECT_ALL);
    }

    else if (index != -1) {
      /* if (!selections->search(index)) { */
      /*   if (!ctrl) { */
      /*     selections->empty(); */
      /*   } */
      /*   selections->add(index); */
      /* } */

      // Click droit sur un dossier
      if (index < path->top()->foldersSize()) {
        Window::showMenu(x, y, Menu::RENAME | Menu::DELETE | Menu::SELECT_ALL);
      }

      // Click droit sur une note
      else {
        Window::showMenu(
            x, y, Menu::ENCODE | Menu::DECODE | Menu::DELETE | Menu::RENAME | Menu::SELECT_ALL);
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
  int index = selections->top();
  switch (menuItem) {
  case Menu::NEW_FOLDER: {
    Window::setTitle("Creating folder");
    string name = Window::showTextField();
    if (name != "" && !path->top()->folderExists(name))
      path->top()->add(new Folder(name));
    Window::setTitle(breadcrumb);
    break;
  }
  case Menu::NEW_NOTE: {
    Window::setTitle("Creating note");
    string name = Window::showTextField();
    if (name != "" && !path->top()->noteExists(name))
      path->top()->add(new Note(name));
    Window::setTitle(breadcrumb);
    break;
  }
  case Menu::RENAME: {
    // Renommer un dossier
    if (index < path->top()->foldersSize()) {
      Window::setTitle("Renaming " + path->top()->getChildFolderName(index));
      string name =
          Window::showTextField(path->top()->getChildFolderName(index));
      if (name != "")
        path->top()->renameChildFolder(index, name);
    }
    // Renommer une note
    else {
      index -= path->top()->foldersSize();
      Window::setTitle("Renaming " + path->top()->getChildNoteName(index));
      string name = Window::showTextField(path->top()->getChildNoteName(index));
      if (name != "")
        path->top()->renameChildNote(index, name);
    }
    selections->empty();
    Window::setTitle(breadcrumb);
    break;
  }
  case Menu::DELETE: {
    Queue<int> *traversal = selections->traversal(Traversal::ReverseInfix);

    while (traversal->size()) {
      index = traversal->front();
      selections->remove(index);
      // Supprimer un dossier
      if (index < path->top()->foldersSize()) {
        path->top()->deleteChildFolder(index);
      }
      // Supprimer une note
      else {
        index -= path->top()->foldersSize();
        path->top()->deleteChildNote(index);
      }
      traversal->pop();
    }
    break;
  }

  case Menu::ENCODE:
    // TODO : Encoder la note avec la méthode de Huffman
    break;

  case Menu::DECODE:
    // TODO : Décoder la note avec la méthode de Huffman
    break;

  case Menu::SELECT_ALL:
    for (int i = 0; i < path->top()->size(); i++) {
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
  // FIX: breaks when you do smth retarded
  while (path->size()) {
    delete path->top();
    path->pop();
  }
  delete path;
  delete selections;
}
