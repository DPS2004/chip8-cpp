#pragma once

#include <cstdint>
#include "Display.h"
#include "Chip.h"

//A "host" is a class that controls rendering and input, and file management.
class Host {

public:
    virtual void Init();
    virtual void Update(Chip* chip);
    virtual void Draw(Display* display);

    virtual uint16_t GetInput();

    virtual void LoadProgram(std::string filename, Chip* chip);

    virtual void Exit();

    bool GetStop();

protected:
    bool stop;
};

