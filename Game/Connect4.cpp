#include "Connect4.hpp"
#include <stdexcept>

void Connect4::run()
{
    con.setForecolor(CColor::Black);
    con.setBackcolor(CColor::DarkOliveGreen1);
    SM->ManageScenes(con);
}