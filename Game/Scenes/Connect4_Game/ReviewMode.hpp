#pragma once
#include <iostream>
#include <stack>
#include <array>

class Review
{
public:
    struct Moves
    {
        Moves() : Player(0), X(-1), Y(-1)
        {}
        
        Moves(int _Player, int _X, int _Y) : Player(_Player), X(_X), Y(_Y)
        {}


        int Player;
        int X;
        int Y;
    };

    Review();
    ~Review();

    void add(int Player, int X, int Y);    
    void clear();
    bool isEmpty();

    Moves& operator[](int index);
    Moves& getLastMove();
    std::stack<Moves> getHistory();
private:
    std::array<Moves, 3> LastMoves;
    std::stack<Moves> Hist;
};