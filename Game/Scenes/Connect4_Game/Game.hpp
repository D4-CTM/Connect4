#pragma once
#include "../Timer/Timer.hpp"
#include "ReviewMode.hpp"
#include "TextConsole.h"
#include "Tiles.hpp"

class Game
{
public:
    Game(Review*& Review, Timer*& _Timers);
    ~Game();

    void RunScene(TextConsole& con, int* scene);
private:
    void winnerFormation(TextConsole& con, int _Row, int _Col, CColor nColor);
    void hotkey(TextConsole& con, int* Scene, int Key);
    void KeyHandler(TextConsole& con, int* scene);
    void endGame(TextConsole& con, int* scene);
    bool isPositionValid(int Row, int Col);
    void winAnimation(TextConsole& con);
    void DrawSelector(TextConsole& con);
    bool PlaceToken(TextConsole& con);
    void DrawBoard(TextConsole& con);
    void showTurn(TextConsole& con);
    void showTime(TextConsole& con);
    void Rewind(TextConsole& con);
    void resume(TextConsole& con);
    void MovePointer(int neoPos);
    void RestartBoard();
    int getRow(int Pos);

    Timer* Timers;
    //RM - Review Mode
    Review* RM;
    Tiles** Tile;
    const int Row;
    const int Col;
    int initialCol;
    int initialRow;
    int finalRow;
    int finalCol;
    int actCol;
    int actRow;
    int Turn;
    //RT - Return turn
    int RT;
};