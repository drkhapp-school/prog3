#include <SDL2/SDL_events.h>

class Event {
private:
  static SDL_Event sdlEvent;

public:
  static const unsigned int &getType();
  static const unsigned int &getWindowId();
  static const unsigned char &getWindowEvent();
  static const int &poll();
};
