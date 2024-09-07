#include "ReviewMode.hpp"

Review::Review()
{}

Review::~Review()
{
    clear();
    std::cout << "Destroyed \'REVIEW MODE\'" << std::endl;
}

void Review::add(int Player, int X, int Y)
{
    Hist.push(Review::Moves(Player, X, Y));

    if (LastMoves.at(1).Player > 0) LastMoves.at(2) = LastMoves.at(1);
    if (LastMoves.at(0).Player > 0) LastMoves.at(1) = LastMoves.at(0);
    
    LastMoves.at(0) = Hist.top();
}

void Review::clear()
{
    while (!Hist.empty()) Hist.pop();
    LastMoves.at(0).Player = 0;
    LastMoves.at(1).Player = 0;
    LastMoves.at(2).Player = 0;
}

bool Review::isEmpty()
{ return Hist.empty(); }

Review::Moves& Review::operator[](int index)
{
    if (index >= 0 && index < 3)
    {
        return LastMoves.at(index);
    }
    throw std::runtime_error("INDEX OUT OF BOUNDS");
}

Review::Moves &Review::getLastMove()
{ return Hist.top(); }

std::stack<Review::Moves> Review::getHistory()
{ return Hist; }
