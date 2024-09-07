#ifndef __GAME_H__
#define __GAME_H__
#include "TextConsole.h"
#include "Scenes/SceneManager.hpp"

class Connect4: public CClient {
public:
    Connect4(TextConsole& con): CClient(con), SM(new SceneManager())
    {}

    ~Connect4()
    {
        delete SM;
    }

    void run() override;
private:
    SceneManager* SM;
};

#endif