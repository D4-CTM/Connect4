#pragma once
#include "RankingManager.hpp"
#include "TextConsole.h"

//This class is in charge of showing the Ranking, yeah, the frontend
class RankingScene
{
public:

    RankingScene();
    ~RankingScene();

    void RunScene(TextConsole& con, int* Scene);
    RankingManager*& getRankManager();

private:
    void KeyHandler(TextConsole& con, int* Scene);
    void initScene(TextConsole& con);

    RankingManager* Rank;
};