#include "RankingScene.hpp"

RankingScene::RankingScene()
: Rank(new RankingManager())
{}

RankingScene::~RankingScene() 
{ 
    std::cout << "Destroyed \'RANKING SCENE\'" << std::endl;
    delete Rank; 
}

void RankingScene::RunScene(TextConsole &con, int *Scene)
{
    con.clearScreen();
    initScene(con);

    con.flushKeybuffer();
    while (*Scene == 1 && con.isActive())
    {
        KeyHandler(con, Scene);
    }

}

RankingManager*& RankingScene::getRankManager()
{ return Rank; }

void RankingScene::KeyHandler(TextConsole &con, int* Scene)
{
    uint32_t key = con.getKey();
    if (key != SDLK_UNKNOWN) 
    {
        switch (key) 
        {
            case SDLK_BACKSPACE:
            case SDLK_ESCAPE:
                *Scene = 0;
            break;
        }
        con.refresh();
    }
}

void RankingScene::initScene(TextConsole &con)
{
    con.setCursor(0,0);
    //  ESC IMG (kinga)
    //  \x94\x95
    con << "Presione \x94\x95 para regresar";
    auto Color = con.getForecolor();

    for (int i = 0; i < 5; i++)
    {
        switch (i)
        {
            case 0: con.setForecolor(CColor::Gold3);
            break;
            case 1: con.setForecolor(CColor::Silver);
            break;
            case 2: con.setForecolor(CColor::SandyBrown);
            break;
            default: con.setForecolor(CColor::Black);
        }
        con.setCursor(5 + (i * 2), 5);
        con << (i + 1) << ". ";
        con.setForecolor(Color);
        con << Rank->getUserData(i);
    }

}
