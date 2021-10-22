#include <map>

#include "Event.hpp"
#include "Window.hpp"

using namespace std;

class Application {
private:
  map<unsigned int, Window *> windows;

  static Application *instance;

public:
  Application();
  ~Application();

  void addWindow(Window *window);
  void start();

  static Application *getInstance();
};
