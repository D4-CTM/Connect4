#pragma once
#include "TextConsole.h"

namespace MenuRender
{
    /*
    *   Menu Items:
    *   
    *   Logo 8x2
    *   Tile:
    *   \x80 -> \x87
    */

    inline void setOption1(TextConsole& con)
    {
        auto auxClr = con.getForecolor();

        con.setCursor(8,5);

        con.setForecolor(CColor::White);
        con << "> ";

        con.setForecolor(CColor::DarkRed2);
        con << "Jugar \'Connect 4\'";

        con.setCursor(10, 5);
        con << "> ";

        con.setForecolor(auxClr);
    }

    inline void setOption2(TextConsole& con)
    {
        auto auxClr = con.getForecolor();

        con.setCursor(10,5);

        con.setForecolor(CColor::White);
        con << "> ";

        con.setForecolor(CColor::DarkRed2);
        con << "Ver ranking";

        con.setCursor(8, 5);
        con << "> ";

        con.setForecolor(auxClr);
    }

    inline void RenderTitle(TextConsole& con)
    {
        auto Color = con.getForecolor();

        con.setCursor(4, 15);
        con.setForecolor(CColor::DarkRed2);
        con << "\x80\x81\x82\x83\x84\x85\x86\x87";

        setOption2(con);
        setOption1(con);

        con.setCursor(con.getRowCount() - 1, 0);
        con << "Developed by: Josh";
        con.setForecolor(Color);
    }

}