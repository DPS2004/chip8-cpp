#pragma once

#include <cstdint>
#include "Display.h"
#include "Chip.h"

enum HostState{
    SELECT_PROGRAM,
    RUN_PROGRAM,
    STOP
};

//A "host" is a class that controls rendering and input, and file management.
class Host {

public:
    virtual void Init();
    virtual void Update(Chip* chip);
    virtual void Draw(Display* display);

    virtual uint16_t GetInput();

    virtual void LoadProgram(std::string filename, Chip* chip);

    virtual void InitMenu();
    virtual void UpdateMenu(Chip* chip);
    virtual void DrawMenu();

    virtual void Exit();

    void GetPrograms(std::vector<std::string> *programlist, const std::string& dirpath);

    HostState GetState();

protected:
    //bool stop;
    HostState state;
    std::vector<std::string> programs;


};

