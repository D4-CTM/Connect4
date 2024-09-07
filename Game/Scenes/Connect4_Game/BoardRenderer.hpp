#include <iostream>
#include "TextConsole.h"
#include "ReviewMode.hpp"

namespace BoardRenderer
{
    //font used: ter-232b.psf
    /*
    *   100 - filas
    *   30  - columnas
    *
    *   FONT DATA:
    * 
    *   Player 1 token:
    *   \x2 -> \x9
    * 
    *   Player 2 token:
    *   \x10 -> \x17
    * 
    *   "I guess it has some use" block:
    *   \x18
    * 
    *   Block tile:
    *   \x19
    * 
    *   Space Tile:
    *   \x20
    * 
    *   Selector:
    *   \x96 -> \x99
    * 
    *   Board size
    *   42x19
    *   
    *   Token P1:
    *   replace chars of: $ %
    * 
    *   Token P2:
    *   replace chars of: { }
    */
    const CColor P1_TOKEN = CColor::Red;
    const CColor P2_TOKEN = CColor::Yellow;

    inline const void RenderSelector(TextConsole& con, int Row, int Col, int actPos)
    {
        auto Color = con.getForecolor();
        for (int i = 0; i < 7; i++)
        {
            con.setForecolor((i == actPos) ? CColor::Black : CColor::White);
            con.setCursor(Row, 1 + Col + (i * 5));
            con << "\x96\x97\x98\x99";   
        }
        con.setForecolor(Color);
    }

    inline const void RenderBlock(TextConsole& con, int Col, int Row, int Owner)
    {
        auto Color = con.getForecolor();
        con.setForecolor(CColor::Blue);
        con.setCursor(Row, Col);
        con << "\x19" << "\x19\x19\x19\x19" << "\x19";

        switch (Owner)
        {

            //this draw's the token for the player 1
            case 1:
                con.setCursor(Row + 1, Col);
                con << "\x19";
                con.setForecolor(P1_TOKEN);
                con << "\x2\x3\x4\x5"; 
                con.setForecolor(CColor::Blue);
                con << "\x19";
                con.setCursor(Row + 2, Col);
                con << "\x19";
                con.setForecolor(P1_TOKEN);
                con << "\x6\x7\x8\x9"; 
                con.setForecolor(CColor::Blue);
                con << "\x19";
            break;

            //this draw's the token for the player 2
            case 2:
                con.setCursor(Row + 1, Col);
                con << "\x19";
                con.setForecolor(P2_TOKEN);
                con << "\x10\x11\x12\x13"; 
                con.setForecolor(CColor::Blue);
                con << "\x19";
                con.setCursor(Row + 2, Col);
                con << "\x19";
                con.setForecolor(P2_TOKEN);
                con << "\x14\x15\x16\x17"; 
                con.setForecolor(CColor::Blue);
                con << "\x19";
            break;

            //If the owner is set to anything rather than 1 or 2 we'll render a blank space
            default:
                con.setCursor(Row + 1, Col);
                con << "\x19" << "\x20\x20\x20\x20" << "\x19";
                con.setCursor(Row + 2, Col);
                con << "\x19" << "\x20\x20\x20\x20" << "\x19";

        }

        con.setCursor(Row + 3, Col);
        con << "\x19" << "\x19\x19\x19\x19" << "\x19";
        con.setForecolor(Color);
    }

    inline void RenderHistory(TextConsole& con, Review& RM)
    {
        con.setCursor(0, 0);
        auto Color = con.getForecolor();
        con << "Historial:\n";

        for (int i = 0; i < 3; i++)
        {
            if (RM[i].Player == 0) break;
            
            if (RM[i].Player == 1) {
                con.setForecolor(P1_TOKEN);
                con << "$%";
            } else {
                con.setForecolor(P2_TOKEN);
                con << "{}";
            }

            con << "[" << RM[i].X << ", " << RM[i].Y << "]\n";
        }

        con.setForecolor(Color);
    }

    inline void goBack(TextConsole& con, Review& RM, int index)
    {
        if (index == 0 && RM[0].Player != 0) 
        {
            con.setCursor(0, 12);
            con << "<- REVIEW MODE ->";
        }

        if (RM[index].Player != 0) RenderBlock(con, 2 + (RM[index].X * 5), 5 + (RM[index].Y * 3), 0);
    }

    inline void printBlockAt(TextConsole& con, int Owner, int Col, int Row, CColor nColor)
    {
        auto Color = con.getForecolor();
        con.setForecolor(CColor::Blue);
        con.setCursor(Row, Col);
        con << "\x19" << "\x19\x19\x19\x19" << "\x19";


        switch (Owner)
        {

            //this draw's the token for the player 1
            case 1:
                con.setCursor(Row + 1, Col);
                con << "\x19";
                con.setForecolor(nColor);
                con << "\x2\x3\x4\x5"; 
                con.setForecolor(CColor::Blue);
                con << "\x19";
                con.setCursor(Row + 2, Col);
                con << "\x19";
                con.setForecolor(nColor);
                con << "\x6\x7\x8\x9"; 
                con.setForecolor(CColor::Blue);
                con << "\x19";
            break;

            //this draw's the token for the player 2
            case 2:
                con.setCursor(Row + 1, Col);
                con << "\x19";
                con.setForecolor(nColor);
                con << "\x10\x11\x12\x13"; 
                con.setForecolor(CColor::Blue);
                con << "\x19";
                con.setCursor(Row + 2, Col);
                con << "\x19";
                con.setForecolor(nColor);
                con << "\x14\x15\x16\x17"; 
                con.setForecolor(CColor::Blue);
                con << "\x19";
            break;

            //If the owner is set to anything rather than 1 or 2 we'll render a blank space
            default:
                con.setCursor(Row + 1, Col);
                con << "\x19" << "\x20\x20\x20\x20" << "\x19";
                con.setCursor(Row + 2, Col);
                con << "\x19" << "\x20\x20\x20\x20" << "\x19";

        }
        con.setCursor(Row + 3, Col);
        con << "\x19" << "\x19\x19\x19\x19" << "\x19";
        con.setForecolor(Color);
    }

    inline void resume(TextConsole& con, Review& RM)
    {
        for (int i = 0; i < 3; i++)
        {
            if (RM[i].Player == 0) break;
            RenderBlock(con, 2 + (RM[i].X * 5), 5 + (RM[i].Y * 3), RM[i].Player);
        }
    }

}