#include <stack>
#include <queue>
//#include "BSTree.hpp"
//#include "AVLTree"
#include "Folder.hpp"

using namespace std;

Folder* root;
stack<Folder*>* path;
//AVLTree<int>* selections;

int getIndex(const int& x, const int& y) {
	// TODO : Retourner l'indice de l'�l�ment click�
	return -1;
}

void onInit() {
	// TODO : Initialisations
}

void onRefresh() {
	// TODO : Afficher le contenu du dossier actuel
}

void onWindowClick(const int& x, const int& y, const bool& button, const bool& ctrl) {
	if (button) {
		// TODO : Click sur un dossier ou une note du dossier actuel
	}
	else {
		// TODO : Afficher le menu
	}
}

void onMenuClick(const unsigned int& menuItem) {
	switch (menuItem) {
	case Menu::NEW_FOLDER:
		// TODO : Cr�er un nouveau dossier dans le dossier actuel
		break;

	case Menu::NEW_NOTE:
		// TODO : Cr�er une nouvelle note dans le dossier actuel
		break;

	case Menu::RENAME:
		// TODO : Renommer le dossier ou la note
		break;

	case Menu::DELETE:
		// TODO : Supprimer le ou les dossiers, et tout ce qu'ils contiennent, et la ou les notes s�lectionn�s
		break;

	case Menu::ENCODE:
		// TODO : Encoder la note avec la m�thode de Huffman
		break;

	case Menu::DECODE:
		// TODO : D�coder la note avec la m�thode de Huffman
		break;

	case Menu::SELECT_ALL:
		// TODO : S�lectionner tous les dossiers et notes du dossier actuel
		break;
	}
}

void onQuit() {
	// TODO : Lib�rations
}
