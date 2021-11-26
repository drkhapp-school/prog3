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

inline Folder *root;
inline Stack<Folder *> *path;
// AVLTree<int>* selections;

/**
 * @brief Obtention du centre d'un icône selon le texte envoyée.
 *
 * @param index L'indice de l'icône
 * @param name Le texte que l'on veut centrer
 *
 * @return Position du texte, en pixels, sur l'axe des x
 */
inline int centerText(int index, string name) {
  return ((Window::getIconWidth() - Window::getStringWidth(name)) / 2) +
         (Window::getIconWidth() * (index));
}

inline void drawItem(Icon icon, string name, int x, int y,
                     bool selected = false) {
  if (Window::getStringWidth(name) >= Window::getIconWidth()) {
    name.resize(10);
    name.replace(name.end(), name.end() - 3, "...");
  }
  Window::drawIcon(icon, x * Window::getIconWidth(),
                   y * Window::getIconHeight(), selected);
  Window::drawString(name, centerText(x, name),
                     (y + 0.75) * Window::getIconHeight());
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
  return -1;
}

/**
 * @brief Automatiquement appelée lorsque la fenêtre s'ouvre
 */
inline void onInit() {
  // TODO : Initialisations
  root = new Folder("/");
  path = new Stack<Folder *>();
  path->push(root);
  root->createFolder(new Folder("hiii"));
  root->createFolder(new Folder("epic files"));
  root->createFolder(new Folder("fucking long ass name like what the fuck"));
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
}

/**
 * @brief Automatiquement appelée environ 60 fois par seconde
 */
inline void onRefresh() {
  // TODO : Afficher le contenu du dossier actuel
  // Get the current folder's contents
  vector<Folder *> folders = path->top()->getFolders();
  vector<Note *> notes = path->top()->getNotes();
  int columns = Window::getWidth() / Window::getIconWidth();
  int index = 0;
  int widthIndex = 0;
  int heightIndex = 0;

  // Root folder
  Window::drawIcon(Icon::FOLDER, 0, 0);
  Window::drawString("..", centerText(index, ".."),
                     Window::getIconHeight() * 0.75);
  index++;

  // All folders
  for (Folder *item : folders) {
    if (!(index % columns)) {
      heightIndex++;
      widthIndex = 0;
    } else {
      widthIndex++;
    }
    index++;

    drawItem(Icon::FOLDER, item->getName(), widthIndex, heightIndex);
  }

  // All notes
  for (Note *item : notes) {
    if (!(index % columns)) {
      heightIndex++;
      widthIndex = 0;
    } else {
      widthIndex++;
    }
    index++;
    drawItem(Icon::NOTE, item->getName(), widthIndex, heightIndex);
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
    // TODO : Créer une nouvelle note dans le dossier actuel
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
  // TODO : Libérations
}
