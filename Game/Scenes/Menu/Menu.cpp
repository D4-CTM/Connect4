#include "Menu.hpp"

void Menu::RunScene(TextConsole &con, int *scene)
{
    Option = 0;
    con.clearScreen();
    MenuRender::RenderTitle(con);

    con.flushKeybuffer();
    while(*scene == 0 && con.isActive())
    {
        keyHandler(con, scene);
    }

}

void Menu::keyHandler(TextConsole &con, int *scene)
{
    uint32_t key = con.getKey();
    if (key != SDLK_UNKNOWN) 
    {
        switch (key) 
        {
            case SDLK_1:
                *scene = 2;
            break;            

            case SDLK_2:
                *scene = 1;
            break;

            case SDLK_w:
            case SDLK_s:
            case SDLK_UP:
            case SDLK_DOWN:
                Option = (Option == 0)? 1 : 0;
                if (Option == 1) MenuRender::setOption2(con);
                else MenuRender::setOption1(con);
            break;

            case SDLK_SPACE:
            case 13: //13 - SLK_Enter
                *scene = (Option == 0)? 2 : 1;
            break;

        }
        con.refresh();
    }
}
