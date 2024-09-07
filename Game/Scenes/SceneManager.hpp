#pragma once
#include <iostream>
#include "TextConsole.h"
#include "Connect4_Game/Game.hpp"
#include "Menu/Menu.hpp"
#include "Ranking/RankingScene.hpp"
#include "Connect4_Game/ReviewMode.hpp"
#include "ResultScreen/ResultScene.hpp"
#include "Timer/Timer.hpp"

class SceneManager
{
public:
    SceneManager() : Scene(0), Timers(new Timer[2]), _Review(new Review()), C4(new Game(_Review, Timers)), _Menu(new Menu()), Rank(new RankingScene()), RS(new Result(Rank->getRankManager(), _Review, Timers))
    {}

    ~SceneManager()
    {
        delete [] Timers;
        delete _Review;
        delete _Menu;
        delete Rank;
        delete RS;
        delete C4;
    }

    void ManageScenes(TextConsole& con);
private:
    RankingScene* Rank;
    Review* _Review;
    Timer* Timers;
    Menu* _Menu;
    Result* RS;
    Game* C4;
    int Scene;
};
