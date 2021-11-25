#include <cmath>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

using namespace std;

enum Icon { FOLDER, NOTE, HUFFMAN };
enum Menu {
  NEW_FOLDER = 1,
  NEW_NOTE = 2,
  RENAME = 4,
  DELETE = 8,
  ENCODE = 16,
  DECODE = 32,
  SELECT_ALL = 64
};

class Window {
public:
  Window();
  ~Window();

  /**
   * @brief Affichage d'un icône dans la fenêtre
   *
   * @param icon Icône à afficher
   * @param x Position, en pixels, sur l'axe des x
   * @param y Position, en pixels, sur l'axe des y
   * @param selected Si l'icône est sélectionné
   */
  static void drawIcon(const Icon &icon, const int &x, const int &y,
                       const bool &selected = false);

  /**
   * @brief Affichage d'une chaîne de caractères dans la fenêtre
   *
   * @param text Chaîne de caractères à afficher
   * @param x Position, en pixels, sur l'axe des x
   * @param y Position, en pixels, sur l'axe des y
   */
  static void drawString(const string &text, const int &x, const int &y);

  /**
   * @brief Obtention de la hauteur actuelle de la fenêtre
   *
   * @return Hauteur, en pixels, de la fenêtre
   */
  static int getHeight();

  /**
   * @brief Obtention de la hauteur d'un icône
   *
   * @return Hauteur, en pixels, d'un icône 
   */
  static int getIconHeight();

  /**
   * @brief Obtention de la largeur d'un icône
   *
   * @return Largeur, en pixels, d'un icône 
   */
  static int getIconWidth();

  /**
   * @brief Obtention de la largeur d'un icône
   *
   * @param text Chaîne de caractères à obtenir la largeur
   * @return Largeur, en pixels, de la chaîne de caractères
   */
  static int getStringWidth(const string &text);

  /**
   * @brief Obtention de la largeur actuelle de la fenêtre
   *
   * @return Largeur, en pixels, de la fenêtre
   */
  static int getWidth();

  static bool open(void (*OnInit)(), void (*OnMenuClick)(const unsigned int &),
                   void (*OnRefresh)(),
                   void (*OnWindowClick)(const int &, const int &, const bool &,
                                         const bool &),
                   void (*OnQuit)());

  /**
   * @brief Définition du titre de la fenêtre
   *
   * @param title Titre de la fenêtre
   */
  static void setTitle(const string &title);

  /**
   * @brief Affichage du menu contextuel
   *
   * @param x Position, en pixels, sur l'axe des x
   * @param y Positions, en pixels, sur l'axe des y
   * @param enables Éléments disponibles du menu
   */
  static void showMenu(const int &x, const int &y,
                       const unsigned int &enables = 0);

  /**
   * @brief
   *
   * @param text
   *
   * @return
   */
  static string showTextField(const string &text = "");

private:
  static TTF_Font *font, *textFont;
  static unsigned int enableItems;
  static Window *instance;
  static bool isMenu;
  static SDL_Texture *icons, *menu, *menuItems[7], *textField, *textBox,
      *textTexture;
  static SDL_Event sdlEvent;
  static SDL_Rect dstRect, itemRect, menuRect, srcRect, textRect, textFieldRect,
      textBoxRect;
  static void (*OnMenuClick)(const unsigned int &);
  static void (*OnRefresh)();
  static void (*OnWindowClick)(const int &, const int &, const bool &,
                               const bool &);

  SDL_Renderer *sdlRenderer;
  SDL_Window *sdlWindow;
};
