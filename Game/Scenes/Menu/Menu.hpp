#pragma once
#include "TextConsole.h"
#include "MenuRenderer.hpp"
#include <iostream>

class Menu
{
public:
    Menu() : Option(0)
    {}

    ~Menu()
    {
        std::cout << "Destroyed \'MENU\'" << std::endl;   
    }

    void RunScene(TextConsole& con, int* scene);

private:
    void keyHandler(TextConsole& con, int* scene);
    int Option;
};