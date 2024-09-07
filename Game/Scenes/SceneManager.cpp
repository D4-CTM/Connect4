#include "SceneManager.hpp"

void SceneManager::ManageScenes(TextConsole &con)
{
    while(con.isActive())
    {
        con.flushKeybuffer();
        switch (Scene)
        {
            //Main menu
            case 0:
                _Menu->RunScene(con, &Scene);
            break;

            //Ranking and stuff
            case 1:
                Rank->RunScene(con, &Scene);
            break;

            //Actual game
            case 2:
                C4->RunScene(con, &Scene);
            break;

            case 3:
            case 4:
                RS->RunScene(con, &Scene);
            break;
        }
    }
}