#pragma once

//A "host" is a class that controls rendering and input, and file management.
class Host {

public:
    virtual void Init();
    virtual void Update();
    virtual void Draw();

    virtual int GetInput();

};

