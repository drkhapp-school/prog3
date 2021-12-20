/**
 * @file Note.hpp
 * @brief Fichier contenant du texte.
 * @author 1927230 - Jean-Philippe
 * @version 1.0.0
 * @date 2021-12-21
 */
#include <string>

using std::string;

class Note {
private:
    string name;
    string content;

public:
    Note(string name, string content = "") {
        this->name = name;
        this->content = content;
    }

    ~Note() {}

    void rename(string name) { this->name = name; }
    void edit(string content) { this->content = content; }
    string getName() { return name; }
    string getContent() { return content; }
};
