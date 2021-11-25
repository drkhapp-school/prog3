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

public:
  // TODO : Implémentation des méthodes nécessaires
};
