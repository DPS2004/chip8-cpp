#pragma once

#define CHIPDISPLAYWIDTH 64
#define CHIPDISPLAYHEIGHT 32

//Stores the current display state, and functions relating to it.
class Display {
public:
    Display();
    void Clear();

    bool* data;
};
