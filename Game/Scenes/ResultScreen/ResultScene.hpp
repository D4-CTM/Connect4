#pragma once
#include <iostream>
#include "../Ranking/RankingManager.hpp"
#include "../Connect4_Game/ReviewMode.hpp"
#include "../Timer/Timer.hpp"
#include "TextConsole.h"

class Result
{
public:
    Result(RankingManager*& _RM, Review*& __Review, Timer*& _Timers);
    ~Result();

    void RunScene(TextConsole& con, int* Scene);
private:
    void keyHandler(TextConsole& con, int* Scene, int Points);
    void itIsDraw(TextConsole& con, int* Scene);
    void itIsWin(TextConsole& con, int* Scene);
    void changeChar(TextConsole& con, int NC);
    void changePos(TextConsole& con, int NP);
    std::string getNickname();
    int getPoints();

    Timer* Timers;
    //RM - Ranking Manager
    RankingManager* RM;
    //RVW - Review
    Review* RVW; 
    int Pos;
    char C1;
    char C2;
    char C3;

};