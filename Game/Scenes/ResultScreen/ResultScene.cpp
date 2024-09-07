#include "ResultScene.hpp"

//Implement the modificable user

Result::Result(RankingManager*& _RM, Review*& __Review, Timer*& _Timers) : RM(_RM), Timers(_Timers), RVW(__Review), Pos(0), C1(' '), C2(' '), C3(' ')
{}

Result::~Result()
{
    std::cout << "Destroyed \'RESULT SCREEN\'" << std::endl;
}

void Result::RunScene(TextConsole &con, int *Scene)
{
    con.clearScreen();
    C1 = 'A';
    C2 = 'A';
    C3 = 'A';

    if (*Scene == 4)
    {
        itIsWin(con, Scene);
    }
    else itIsDraw(con, Scene);
    *Scene = 0;
}

std::string Result::getNickname()
{
    return std::string{C1, C2, C3};
}

void Result::keyHandler(TextConsole& con, int* Scene, int Points)
{
    uint32_t key = con.getKey();

    if (key != SDLK_UNKNOWN) 
    {
        switch (key) 
        {
            case 13: //Enter
                if (!RM->add(getNickname(), Points)) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Puntaje bajo", "¡No lograste entrar en el ranking, lo sentimos!", nullptr);
                *Scene = 0;
            break;

            case SDLK_ESCAPE:
                *Scene = 0;
            break;

            case SDLK_d:
            case SDLK_RIGHT:
                changePos(con, 1);
            break;

            case SDLK_a:
            case SDLK_LEFT:
                changePos(con, -1);
            break;

            case SDLK_w:
            case SDLK_UP:
                changeChar(con, 1);
            break;

            case SDLK_s:
            case SDLK_DOWN:
                changeChar(con, -1);
            break;
        }

        con.flushKeybuffer();
        con.refresh();
    }
}

void Result::itIsWin(TextConsole& con, int* Scene)
{
    con.setCursor(3, 8);
    auto color = con.getForecolor();
    con.setForecolor(CColor::Black);
    con << "El jugador #" << RVW->getLastMove().Player << " ha ganado";

    int Points = getPoints() + Timers[RVW->getLastMove().Player - 1].timeToScore();
    con.setCursor(4, 7);
    con << "Tiempo restante: " << Timers[RVW->getLastMove().Player - 1].remainingTime();


    con.setCursor(6, 8);
    con << "Puntaje conseguido: " << Points;

    con.setCursor(8,11);
    con << "Ingrese un apodo:";
    con.setForecolor(CColor::Red);
    con.setCursor(9, 18);
    con << C1;
    con.setForecolor(CColor::Black);
    con << C2 << C3;

    con.setCursor(10,0);
    con.setCursor(11, 13);
    con << "Presione \x92\x93";
    con.setCursor(12, 3);
    con << "para intentar entrar en el ranking";
    con.setCursor(13, 13);
    con << "Presione \x94\x95";
    con.setCursor(14, 12);
    con << "para regresar";

    while(*Scene == 4 && con.isActive())
    {
        keyHandler(con, Scene, Points);
    }

    con.setForecolor(color);
}

void Result::changePos(TextConsole &con, int NP)
{
    con.setCursor(9, 18 + Pos);
    con.setForecolor(CColor::Black);
    if (Pos == 0) con << C1;
    else if (Pos == 1) con << C2;
    else if (Pos == 2) con << C3;

    Pos += NP;
    if (Pos < 0) Pos = 2;
    else if (Pos > 2) Pos = 0;

    con.setCursor(9, 18 + Pos);
    con.setForecolor(CColor::Red);
    if (Pos == 0) con << C1;
    else if (Pos == 1) con << C2;
    else if (Pos == 2) con << C3;
}

void validateChar(char& auxC)
{
    switch (auxC)
    {
        case 'Z' + 1:
            auxC = '0';
        break;

        case 'z' + 1:
            auxC = 'A';
        break;

        case 'a' - 1:
            auxC = '9';
        break;

        case 'A' - 1:
            auxC = 'z';
        break;

        case '0' - 1:
            auxC = 'Z';
        break;

        case '9' + 1:
            auxC = 'a';
        break;
    }
}

void Result::changeChar(TextConsole &con, int NP)
{
    if (Pos == 0)
    {
        C1 += NP;
        validateChar(C1);
    }
    else if (Pos == 1)
    {
        C2 += NP;
        validateChar(C2);
    }
    else if (Pos == 2)
    {
        C3 += NP;
        validateChar(C3);
    }


    con.setCursor(9, 18 + Pos);
    con.setForecolor(CColor::Red);
    if (Pos == 0) con << C1;
    else if (Pos == 1) con << C2;
    else if (Pos == 2) con << C3;
}

int Result::getPoints()
{
    auto History = RVW->getHistory();
    int Player = RVW->getLastMove().Player;
    int Points = 100;

    while (!History.empty())
    {
        if (History.top().Player == Player) Points += 10;
        History.pop();
    }

    return Points;
}

void Result::itIsDraw(TextConsole& con, int* Scene)
{
    con.setCursor(3,12);
    auto color = con.getForecolor();
    con.setForecolor(CColor::Black);
    con << "FUE UN EMPATE!";

    con.setCursor(5, 13);
    con << "Presione \x94\x95";
    con.setCursor(6, 12);
    con << "para regresar";
    while ((con.getKey() != SDLK_ESCAPE) && con.isActive());
    con.setForecolor(color);
}