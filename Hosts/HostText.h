#pragma once

#include "../Host.h"
#include "../Display.h"

#define CELL_OFF ' '
#define CELL_ON '#'

class HostText: public Host {
public:
    void Init() override;
    void Update(Chip* chip) override;
    void Draw(Display* display) override;
    int GetInput() override;
    void LoadProgram(std::string filename, Chip* chip)  override;
    void Exit() override;
private:
    int remainingSteps;
    char border;
    std::string borderLine;
};

