#pragma once
#include <iostream>
#include <array>

//This class is in charge of all the logic behind the Ranking, in simple terms: the backend.
class RankingManager
{
public:
    RankingManager();

    ~RankingManager();

    bool add(std::string _Nickname, int _Points);
    std::string getUserData(int index);

private:
    struct User
    {
        std::string Nickname;
        int Points;

        User(std::string _Nickname) : Nickname(_Nickname), Points(0) 
        {}

        User() : Nickname("???"), Points(140)
        {}

        ~User()
        { 
            std::cout << "\t\'" << Nickname << "\' deleted" << std::endl;
        }

        std::string toString()
        { return Nickname + " - " + std::to_string(Points); }
    };
    std::array<User, 5> Rank;

    void initArray(std::string Filename);
    void initFile(std::string Filename);
    void sort();
};
