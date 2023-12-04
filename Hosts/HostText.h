#pragma once

#include "../Host.h"
#include "../Display.h"

#define CELL_OFF ' '
#define CELL_ON '#'

#define PROGRAMDIRECTORY "Programs/"

class HostText: public Host {
public:
    void Init() override;
    void Update(Chip* chip) override;
    void Draw(Display* display) override;

    void UpdateMenu(Chip* chip) override;
    void DrawMenu() override;

    uint16_t GetInput() override;
    void LoadProgram(std::string filename, Chip* chip)  override;
    void Exit() override;
private:
    int remainingSteps;
    char border;
    std::string borderLine;
};

