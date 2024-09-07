#include <iostream>
#include "TextConsole.h"
#include "Connect4.hpp"

int main(int argc, char *argv[])
{

                //Cols - Rows
   TextConsole con(40, 25);

    if (!con.activate()) {
        return 1;
    }
    Connect4 game(con);

    con.run(game);

    return 0;
}