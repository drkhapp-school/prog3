/**
 * @file Folder.hpp
 * @brief Dossier contenant des fichiers et dossiers enfants.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-11-25
 */
#include "Note.hpp"
#include <vector>

using namespace std;

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
  // TODO : Implémentation des méthodes nécessaires
  Folder(string name) { this->name = name; }

  ~Folder() {
    for (Folder *child : folders) {
      delete child;
    }
    for (Note *child : notes) {
      delete child;
    }
    folders.clear();
    notes.clear();
  }

  void addFolder(Folder *item) {
    if (folderExists(item->name))
      return;
    folders.push_back(item);
    sortFolders(0, folders.size() - 1);
  }
  void addFolder(string name) {
    if (folderExists(name))
      return;
    folders.push_back(new Folder(name));
    sortFolders(0, folders.size() - 1);
  }

  void addNote(Note *item) {
    if (noteExists(item->getName()))
      return;
    notes.push_back(item);
    sortNotes(0, notes.size() - 1);
  }
  void addNote(string name) {
    if (noteExists(name))
      return;
    notes.push_back(new Note(name));
    sortNotes(0, notes.size() - 1);
  }

  string getName() { return name; }
  int getSize() { return folders.size() + notes.size(); }
  void rename(string name) { this->name = name; }
  bool folderExists(string name) {
    for (Folder *x : folders)
      if (x->name == name)
        return true;

    return false;
  }
  void deleteChildFolder(int index) {
    delete folders[index];
    folders.erase(folders.begin() + index);
  }

  bool noteExists(string name) {
    for (Note *x : notes)
      if (x->getName() == name)
        return true;

    return false;
  }

  int getFoldersCount() { return folders.size(); }
  Folder *getChildFolder(size_t index) { return folders[index]; }
  string getChildFolderName(size_t index) { return folders[index]->getName(); }
  void renameChildFolder(size_t index, string name) {
    folders[index]->name = name;
    sortFolders(0, folders.size() - 1);
  }

  int getNotesCount() { return notes.size(); }
  string getChildNoteName(size_t index) { return notes[index]->getName(); }
  string getChildNoteContent(size_t index) {
    return notes[index]->getContent();
  }
  void renameChildNote(size_t index, string name) {
    notes[index]->setName(name);
    sortNotes(0, notes.size() - 1);
  }
  void editChildNote(size_t index, string content) {
    notes[index]->setContent(content);
  }
  void deleteChildNote(int index) {
    delete notes[index];
    notes.erase(notes.begin() + index);
  }
};
