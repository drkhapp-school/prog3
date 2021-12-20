#include "TP3.hpp"

int main(int argc, char *argv[]) {
    return Window::open(onInit, onMenuClick, onRefresh, onWindowClick, onQuit);
}
