#include "Game.hpp"

Game::Game(Review*& _Review, Timer*& _Timers) : RM(_Review), Timers(_Timers), Col(7), Row(6), Turn(1), actCol(0), actRow(0), finalCol(0), finalRow(0), initialCol(0), initialRow(0), RT(0)
{
    Tile = new Tiles*[7];
    for (int i = 0; i < Col; i++)
    {
        Tile[i] = new Tiles[6];

        for (int j = 0; j < Row; j++)
        {
            Tile[i][j].setCol(2 + (i * 5));
            Tile[i][j].setRow(5 + (j * 3));
        }

    }
}

Game::~Game()
{
    for (int i = 0; i < 6; i++) {
        delete [] Tile[i];
    }

    delete [] Tile;
    std::cout << "Destroyed \'GAME\'" <<std::endl;
}

void Game::RunScene(TextConsole &con, int *Scene)
{
    RestartBoard();
    con.clearScreen();
    DrawBoard(con);

    showTime(con);
    con.flushKeybuffer();
    while (*Scene == 2 && con.isActive())
    {
        KeyHandler(con, Scene);
    }
}

void Game::KeyHandler(TextConsole &con, int* Scene)
{
    uint32_t key = con.getKey();

    if (!Timers[Turn - 1].isRunning()) Timers[Turn - 1].startTimer();
    if (key != SDLK_UNKNOWN) 
    {
        switch (key) 
        {
            case SDLK_a:
            case SDLK_LEFT:
                if (RT > 0) resume(con);
                MovePointer(-1);
                DrawSelector(con);
            break;

            case SDLK_d:
            case SDLK_RIGHT:
                if (RT > 0) resume(con);
                MovePointer(1);
                DrawSelector(con);
            break;
            
            case 13: //Enter
            case SDLK_s:
            case SDLK_DOWN:
                if (RT > 0) resume(con);
                else if (PlaceToken(con)) {
                    endGame(con, Scene);
                }
            break;

            case SDLK_BACKSPACE:
                if (!RM->isEmpty()) Rewind(con);
            break;

            case SDLK_SPACE:
                if (RT > 0) resume(con);
            break;

            case SDLK_ESCAPE:
                Timers[Turn - 1].pauseTimer();
                Turn = (Turn == 1)? 2 : 1;
                if (!RM->isEmpty()) *Scene = 4;
                else *Scene = 0;
            break;

            case SDLK_1:
                hotkey(con, Scene, 0);
            break;

            case SDLK_2:
                hotkey(con, Scene, 1);
            break;

            case SDLK_3:
                hotkey(con, Scene, 2);
            break;

            case SDLK_4:
                hotkey(con, Scene, 3);
            break;

            case SDLK_5:
                hotkey(con, Scene, 4);
            break;

            case SDLK_6:
                hotkey(con, Scene, 5);
            break;

            case SDLK_7:
                hotkey(con, Scene, 6);
            break;

            default:
                if (RT > 0) resume(con);
        }
        
        con.flushKeybuffer();
        con.refresh();
    }
    if (Timers[Turn - 1].hasChanged()) showTime(con);
}

void Game::endGame(TextConsole &con, int* scene)
{
    const int Player = Tile[actCol][actRow].getOwner();
    int line = 0;

    initialCol = actCol;
    initialRow = actRow;
    if (isPositionValid(actRow + 3, actCol)) 
    {
        for (int i = 1; i < 4; i++)
        {
            if (Tile[actCol][actRow + i] != Player) break;

            if (i == 3)
            {
                finalCol = actCol;
                finalRow = actRow + 3;
                *scene = 4;

                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return ;
            }

        }
    }

    for (int i = 0; i < 4; i++)
    {
        if (!isPositionValid(actRow, actCol + i)) break;

        if (Tile[actCol + i][actRow] == Player) {

            if (i == 3) {
                finalCol = actCol + 3;
                finalRow = actRow;
                initialCol = actCol;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return;
            } else {
                initialCol = actCol + i;
            }

        } else break;

    }

    for (int i = 0; i < 4; i++)
    {
        if (!isPositionValid(actRow, actCol - i)) break;

        if (Tile[actCol - i][actRow] == Player) {

            if ((initialCol - (actCol - i)) == 3) {
                finalCol = actCol - i;
                finalRow = actRow;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return ;
            } else if (i == 3) {
                finalCol = actCol - 3;
                finalRow = actRow;
                initialCol = actCol;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return;
            }


        } else break;
    }

    initialCol = actCol;
    initialRow = actRow;
    for (int i = 0; i < 4; i++)
    {
        if (!isPositionValid(actRow + i, actCol + i)) break;

        if (Tile[actCol + i][actRow + i] == Player) {

            if (i == 3) {
                finalCol = actCol + 3;
                finalRow = actRow + 3;
                initialCol = actCol;
                initialRow = actRow;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return;
            } else {
                initialCol = actCol + i;
                initialRow = actRow + i;
            }

        } else break;

    }

    for (int i = 0; i < 4; i++)
    {
        if (!isPositionValid(actRow - i, actCol - i)) break;

        if (Tile[actCol - i][actRow - i] == Player) {

            if ((initialCol - (actCol - i)) == 3) {
                finalCol = actCol - i;
                finalRow = actRow - i;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return ;
            } else if (i == 3) {
                finalCol = actCol - 3;
                finalRow = actRow - i;
                initialCol = actCol;
                initialRow = actRow;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return;
            }

        } else break;
    }

    initialCol = actCol;
    initialRow = actRow;
    for (int i = 0; i < 4; i++)
    {
        if (!isPositionValid(actRow + i, actCol + i)) break;

        if (Tile[actCol + i][actRow + i] == Player) {

            if (i == 3) {
                finalCol = actCol + 3;
                finalRow = actRow + 3;
                initialCol = actCol;
                initialRow = actRow;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return;
            } else {
                initialCol = actCol + i;
                initialRow = actRow + i;
            }

        } else break;

    }

    for (int i = 0; i < 4; i++)
    {
        if (!isPositionValid(actRow - i, actCol - i)) break;

        if (Tile[actCol - i][actRow - i] == Player) {

            if ((initialCol - (actCol - i)) == 3 && (initialRow - (actRow - i)) == 3) {
                finalCol = actCol - i;
                finalRow = actRow - i;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return ;
            } else if (i == 3) {
                finalCol = actCol - 3;
                finalRow = actRow - i;
                initialCol = actCol;
                initialRow = actRow;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return;
            }

        } else break;
    }

    initialCol = actCol;
    initialRow = actRow;
    for (int i = 0; i < 4; i++)
    {
        if (!isPositionValid(actRow - i, actCol + i)) break;

        if (Tile[actCol + i][actRow - i] == Player) {

            if (i == 3) {
                finalCol = actCol + 3;
                finalRow = actRow - 3;
                initialCol = actCol;
                initialRow = actRow;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return;
            } else {
                initialCol = actCol + i;
                initialRow = actRow - i;
            }

        } else break;

    }

    for (int i = 0; i < 4; i++)
    {
        if (!isPositionValid(actRow + i, actCol - i)) break;

        if (Tile[actCol - i][actRow + i] == Player) {

            if ((initialCol - (actCol - i)) == 3 && ((actRow + i) - initialRow) == 3) {
                finalCol = actCol - i;
                finalRow = actRow + i;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return ;
            } else if (i == 3) {
                finalCol = actCol - 3;
                finalRow = actRow + 3;
                initialCol = actCol;
                initialRow = actRow;
                *scene = 4;
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                winAnimation(con);
                return;
            }

        } else break;
    }

    if (actRow == 0)
    {
        for (int i = 0; i < Col; i++)
        {
            if (Tile[i][0] == 0) break;
            else if (i == (Col - 1)){
                *scene = 3;
                con.playDrawSFX();
                Timers[0].pauseTimer();
                Timers[1].pauseTimer();
                auto BG = con.getBackcolor();
                for (int i = 0; i < 30; i++)
                {
                    con.setBackcolor((i%4 < 2)? CColor::Black : CColor::White);
                    con.clearScreen();
                    con.refresh();
                    con.delayMs(80);
                }
                con.setBackcolor(BG);
                return ;
            } 
        }

    }

}

bool Game::isPositionValid(int Row, int Col)
{ return (Col >= 0 && Col < 7 && Row >= 0 && Row < 6); }

void Game::winAnimation(TextConsole& con)
{
    auto BG = con.getBackcolor();
    CColor Color;
    con.playWinSFX();
    for (int i = 0; i < 30 ; i++)
    {
        con.clearScreen();
        con.setBackcolor((i%4 < 2) ? CColor::White : CColor::Black);
        switch (i%6)
        {
            case 0:
                Color = CColor::Cyan1;
            break;

            case 1:
                Color = CColor::DarkSeaGreen1;
            break;

            case 2:
                Color = CColor::Violet;
            break;

            case 3:
                Color = CColor::SpringGreen1;
            break;
 
            case 4:
                Color = CColor::IndianRed;
            break;

            case 5:
                Color = CColor::MediumPurple;
            break;

        }

        winnerFormation(con, initialRow, initialCol, Color);        
        con.delayMs(80);
    }
    con.setBackcolor(BG);
}

void Game::winnerFormation(TextConsole &con, int _Row, int _Col, CColor nColor)
{
    BoardRenderer::printBlockAt(con, Tile[actCol][actRow].getOwner(), Tile[_Col][_Row].getCol(), Tile[_Col][_Row].getRow(), nColor);
    if (_Row != finalRow || _Col != finalCol)
    {
        if (_Row > finalRow) _Row--;
        else if (_Row < finalRow) _Row++;

        if (_Col > finalCol) _Col--;
        else if (_Col < finalCol) _Col++;

        winnerFormation(con, _Row, _Col, nColor);
    }
}

void Game::RestartBoard()
{
    Timers[0].restartTimer();
    Timers[1].restartTimer();
    initialRow = 0;
    initialCol = 0;
    finalRow = 0;
    finalCol = 0;
    actCol = 0;
    for (int i = 0; i < Col; i++)
    {
        
        for (int j = 0; j < Row; j++)
        {
            Tile[i][j].setOwner(0);
        }

    }
    RM->clear();
    Turn = 1;
}

bool Game::PlaceToken(TextConsole& con)
{
    try {
        actRow = getRow(actCol);
        Tile[actCol][actRow].setOwner(Turn);

        Tile[actCol][actRow].Draw(con);
        RM->add(Turn, actCol, actRow);
        Timers[Turn - 1].pauseTimer();
        Turn = (Turn == 1)? 2 : 1;
        BoardRenderer::RenderHistory(con, *RM);
        showTurn(con);
        showTime(con);
        return true;
    } catch (std::exception e){
        con.playErrorSFX();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Columna llena", "¡Esta columna no tiene espacios disponibles!", nullptr);
    }
    return false;

}

int Game::getRow(int Pos)
{
    if (Pos >= 0 && Pos < 7)
    {

        for (int i = Row - 1; i >= 0; i--)
        {
            if (Tile[Pos][i] == 0) return i;
        }

    } 
    throw std::out_of_range("Position out of index");
}

void Game::Rewind(TextConsole& con)
{
    Timers[Turn - 1].pauseTimer();
    if (RT < 3) 
    {
        BoardRenderer::goBack(con, *RM, RT);
        RT++;
    }
}

void Game::resume(TextConsole &con)
{
    con.setCursor(0,12);
    con << "                 ";

    BoardRenderer::resume(con, *RM);
    RT = 0;
}

void Game::MovePointer(int neoPos)
{
    if ((actCol + neoPos) >= 0 && (actCol + neoPos) < 7) actCol += neoPos;
    else 
    {
        if ((actCol + neoPos) < 0) actCol = 6;

        else if ((actCol + neoPos) <= 7) actCol = 0;
    }
}

void Game::hotkey(TextConsole& con, int* Scene, int Key)
{
    if (actCol == Key)
    {
        if (RT > 0) resume(con);
        else if (PlaceToken(con)) {
            endGame(con, Scene);
        }
    }
    else
    {
        actCol = Key;
        DrawSelector(con);
    }
}

void Game::DrawBoard(TextConsole& con)
{
    showTurn(con);
    for (int i = 0; i < Col; i++)
    {
        
        for (int j = 0; j < Row; j++)
        {
            Tile[i][j].Draw(con);
        }

    }

    DrawSelector(con);
}

void Game::showTurn(TextConsole &con)
{
    auto Color = con.getForecolor();

    con.setCursor(2,14);
    con.setForecolor((Turn == 1)? BoardRenderer::P1_TOKEN : BoardRenderer::P2_TOKEN);
    con << "Turno de: J" << Turn;

    con.setForecolor(Color);
}

void Game::showTime(TextConsole &con)
{
    auto Color = con.getForecolor();
    con.setCursor(3, 16);
    
    con << Timers[Turn - 1].getTime() << " ";
    con.setForecolor(Color);
}

void Game::DrawSelector(TextConsole &con)
{
    BoardRenderer::RenderSelector(con, Tile[0][0].getRow() - 1, Tile[0][0].getCol(), actCol);
}
