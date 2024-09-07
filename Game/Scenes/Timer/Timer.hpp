#pragma once
#include <iostream>
#include <thread>
#include <chrono>

class Timer
{
public:
    Timer();
    ~Timer();

    int getMin();
    bool isRunning();
    void startTimer();
    void pauseTimer();
    int timeToScore();
    void restartTimer();
    bool hasChanged();
    std::string getTime();
    std::string remainingTime();
private:
    void startChrono();

    std::thread chronometer;
    bool Changed, Running;
    int Sec, Min, Hour;
};