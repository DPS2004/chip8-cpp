#pragma once

#include "../Host.h"
#include "../Display.h"

#define CELL_OFF ' '
#define CELL_ON '#'

class HostText: public Host {
public:
    void Init() override;
    void Draw(Display* display) override;
private:
    char border;
    std::string borderLine;
};

