#include "RankingManager.hpp"
#include <fstream>

const std::string FILENAME = "./Game/Ranking.C4";

void RankingManager::initFile(std::string Filename)
{
    std::ifstream rf(Filename);
    std::string line;
    if (!rf)
    {
        std::ofstream wf(Filename);

        char Nick = 'A';
        for (int i = 0; i < 5; i++)
        {
            wf << Nick << Nick << Nick << "\n" << 50 + (50 * i) << '\n'; 
            Nick++;
        }

        wf.close();
    }

    rf.close();
}

void RankingManager::initArray(std::string Filename)
{
    std::ifstream rf(Filename);
    std::string line;

    for (int i = 0; i < 5; i++)
    {
        getline(rf, Rank.at(i).Nickname);
        getline(rf, line);
        Rank.at(i).Points = std::stoi(line);
    }

    rf.close();
}

RankingManager::RankingManager()
{
    initFile(FILENAME);    
    initArray(FILENAME);    
    sort();
}

RankingManager::~RankingManager()
{
    std::ofstream wf(FILENAME);

    for (int i = 0; i < 5; i++)
    {
        wf << Rank.at(i).Nickname << "\n" << Rank.at(i).Points << '\n'; 
    }

    wf.close();

    if (wf.good()) std::cout << "- Data saved" << std::endl;

    std::cout << "Destroyed \'RANKING MANAGER\'" << std::endl;
}

void RankingManager::sort()
{
    int auxPos;
    User* auxUser = new User();
    for (int i = 0; i < 5; i++)
    {
        auxPos = i;
        for (int j = i; j < 5; j++)
        {
            if (Rank.at(i).Points < Rank.at(j).Points) auxPos = j;
        }

        if (auxPos != i)
        {
            auxUser->Nickname = Rank.at(i).Nickname;
            Rank.at(i).Nickname = Rank.at(auxPos).Nickname;
            Rank.at(auxPos).Nickname = auxUser->Nickname;

            auxUser->Points = Rank.at(i).Points;
            Rank.at(i).Points = Rank.at(auxPos).Points;
            Rank.at(auxPos).Points = auxUser->Points;
        }
    }
    auxUser->Nickname = "auxUser - (sort)";
    delete auxUser;
}

bool RankingManager::add(std::string _Nickname, int _Points)
{
    //First loop, this checks out if the nickname doesn't repeat, if it does then we simply insert the new _Points
    for (int i = 0; i < 5; i++)
    {
        if (Rank.at(i).Nickname == _Nickname)
        {
            if (Rank.at(i).Points >= _Points) return false;
            Rank.at(i).Points = _Points;
            sort();
            return true;
        }
    }

    //Second loop, this checks if the new user got enough points to enter the podium, we simply replace where we have enough points
    for (int i = 4; i >= 0; i--)
    {
        if (Rank.at(i).Points <= _Points)
        {
            Rank.at(i).Nickname = _Nickname;
            Rank.at(i).Points = _Points;
            sort();
            return true;
        }
    }

    return false;
}

std::string RankingManager::getUserData(int index)
{
    try {
        return Rank.at(index).toString();
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
        return "??? - 100";
    }
}
