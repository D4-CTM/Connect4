#pragma once
#include "TextConsole.h"
#include "BoardRenderer.hpp"

class Tiles
{
public:
    Tiles();
    
    void Draw(TextConsole& con);
    void setOwner(int _Owner);
    void setRow(int _Row);
    void setCol(int _Col);

    int getOwner();
    int getRow();
    int getCol();

    bool operator==(int val);
    bool operator!=(int val);
private:
    int Owner;
    int Row;
    int Col;
};