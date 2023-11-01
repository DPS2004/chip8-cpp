#include "Display.h"


Display::Display() {
    data = new bool[CHIPDISPLAYWIDTH*CHIPDISPLAYHEIGHT];
    Clear();
}

void Display::Clear() {
    for (int i = 0; i < CHIPDISPLAYWIDTH*CHIPDISPLAYHEIGHT; i++) {
        data[i] = false;
    }
}
