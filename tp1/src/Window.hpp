#pragma once

#include <SDL2/SDL.h>

#include "Maze.hpp"

class Window {
private:
  SDL_Window *sdlWindow;
  SDL_Renderer *sdlRenderer;
  SDL_Rect sdlRect;

public:
  Window();
  ~Window();

  void clear();
  void drawSquare(Square square, const unsigned char &x,
                  const unsigned char &y);
  const unsigned int getId();
  void refresh();

  virtual void onUpdate() = 0;
  virtual void onRefresh() = 0;
};
