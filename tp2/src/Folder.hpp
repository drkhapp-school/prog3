/**
 * @file Folder.hpp
 * @brief Dossier contenant des fichiers et dossiers enfants.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-12-21
 */
#include "Note.hpp"
#include <vector>

using std::swap;
using std::vector;

class Folder {
private:
  string name;
  vector<Folder *> folders;
  vector<Note *> notes;

  void sortFolders(int min, int max) {
    int left = min;
    int right = max;
    int pivot = left;

    while (left != right) {
      if (folders[left]->getName() > folders[right]->getName()) {
        swap(folders[left], folders[right]);
        pivot = left + right - pivot;
      }

      pivot == left ? right-- : left++;
    }

    if (min < pivot - 1)
      sortFolders(min, pivot - 1);
    if (max > pivot + 1)
      sortFolders(pivot + 1, max);
  }

  void sortNotes(int min, int max) {
    int left = min;
    int right = max;
    int pivot = left;

    while (left != right) {
      if (notes[left]->getName() > notes[right]->getName()) {
        swap(notes[left], notes[right]);
        pivot = left + right - pivot;
      }

      pivot == left ? right-- : left++;
    }

    if (min < pivot - 1)
      sortNotes(min, pivot - 1);
    if (max > pivot + 1)
      sortNotes(pivot + 1, max);
  }

public:
  Folder(string name) { this->name = name; }

  ~Folder() {
    for (Folder *child : folders)
      delete child;

    for (Note *child : notes)
      delete child;

    folders.clear();
    notes.clear();
  }

  int size() { return folders.size() + notes.size(); }

  string getName() { return name; }

  // Méthodes pour les dossiers enfants

  void add(Folder *item) {
    if (folderExists(item->name))
      return;
    folders.push_back(item);
    sortFolders(0, folders.size() - 1);
  }

  bool folderExists(string name) {
    for (Folder *x : folders)
      if (x->name == name)
        return true;
    return false;
  }

  int foldersSize() { return folders.size(); }

  Folder *getChildFolder(size_t index) { return folders[index]; }

  string getChildFolderName(size_t index) { return folders[index]->name; }

  void renameChildFolder(size_t index, string name) {
    if (folderExists(name))
      return;
    folders[index]->name = name;
    sortFolders(0, folders.size() - 1);
  }

  void deleteChildFolder(int index) {
    delete folders[index];
    folders.erase(folders.begin() + index);
  }

  // Méthodes pour les notes enfants

  void add(Note *item) {
    if (noteExists(item->getName()))
      return;
    notes.push_back(item);
    sortNotes(0, notes.size() - 1);
  }

  bool noteExists(string name) {
    for (Note *x : notes)
      if (x->getName() == name)
        return true;
    return false;
  }

  int notesSize() { return notes.size(); }

  string getChildNoteName(size_t index) { return notes[index]->getName(); }

  void renameChildNote(size_t index, string name) {
    if (noteExists(name))
      return;
    notes[index]->rename(name);
    sortNotes(0, notes.size() - 1);
  }

  string getChildNoteContent(size_t index) {
    return notes[index]->getContent();
  }

  void editChildNote(size_t index, string content) {
    notes[index]->edit(content);
  }

  void deleteChildNote(int index) {
    delete notes[index];
    notes.erase(notes.begin() + index);
  }
};
