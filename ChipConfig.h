/*
Author        : Dimitri Sophinos
Class         : CSI - 240 : Advanced Programming
Assignment    : Final project
Due Date      : 12/5/23 11:59PM
*/
/*
Project Description :
Create an interpreter for the CHIP-8 system.

Certification of Authenticity :

I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/
#pragma once


#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>

class ChipConfig {
public:
    ChipConfig();
    ChipConfig(const std::string& filename);
    void LoadConfig(const std::string& filename);

	std::ifstream configInput;
	
    int screenwidth;
    int screenheight;
    int ips;
    int memsize;
    bool vyshift;
    bool vxoffsetjump;
    bool indexoverflow;
    bool tempstoreload;
    bool waitforrelease;
    bool dotimedupdate;
    int pagesize;
};
