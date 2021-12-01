/**
 * @file Folder.hpp
 * @brief Dossier contenant des fichiers et dossiers enfants.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-11-25
 */
#include <vector>

#include "Note.hpp"

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
  // TODO : Impl�mentation des m�thodes n�cessaires
  Folder(string name) { this->name = name; }

  ~Folder() {}

  void createFolder(Folder *item) {
    folders.push_back(item);
    sortFolders(0, folders.size() - 1);
  }

  void createNote(Note *item) {
    notes.push_back(item);
    sortNotes(0, notes.size() - 1);
  }

  string getName() { return name; }
  int getSize() { return folders.size() + notes.size();}
  void rename(string name) { this->name = name; }

  int getFoldersCount() { return folders.size(); }
  string getChildFolderName(size_t index) { return folders[index]->name; }
  void renameChildFolder(size_t index, string name) {}

  int getNotesCount() { return notes.size(); }
  string getChildNoteName(size_t index) { return notes[index]->getName(); }
  string getChildNoteContent(size_t index) { return notes[index]->getContent(); }
  void renameChildNote(size_t index, string name) {}
  void editChildNote(size_t index, string name) {}
};
