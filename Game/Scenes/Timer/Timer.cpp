#include "Timer.hpp"

Timer::Timer() : Sec(0), Min(0), Hour(0), Running(false), Changed(false)
{}

Timer::~Timer() 
{ 
    if (Running) pauseTimer();
    std::cout << "Destroyed \'TIMER\'" << std::endl; 
}

int Timer::getMin()
{ return Min; }

bool Timer::isRunning()
{ return Running; }

int Timer::timeToScore()
{
    if (Min < 10) return (600 - (Sec + (Min * 60))) * 10;

    return 0;
}

void Timer::startTimer()
{
    Running = true;
    chronometer = std::thread(&Timer::startChrono, this);
}

void Timer::pauseTimer()
{
    if (Running)
    {
        Running = false;
        if (chronometer.joinable()) chronometer.join();
    }
}

void Timer::restartTimer()
{
    Hour = 0;
    Min = 0;
    Sec = 0;
}

bool Timer::hasChanged()
{
    if (Changed) 
    {
        Changed = false;
        return true;
    }
    return false;
}

std::string Timer::getTime()
{
    std::string Result = std::to_string(Hour);
    Result += ":";
    Result += std::to_string(Min);
    Result += ":";
    Result += std::to_string(Sec);
    return Result;
}

std::string Timer::remainingTime()
{
    std::string result = "00:";
    result += std::to_string(9 - Min) + ":";
    result += std::to_string(60 - Sec);
    return (Min < 10) ? result : "00:00:00";
}

void Timer::startChrono()
{
    using Time = std::chrono::steady_clock;
    using float_sec = std::chrono::duration<float>;
    
    auto lastTime = Time::now();
    while (Running)
    {
        if ((Time::now() - lastTime) >= (float_sec) (1))
        {
            Sec++;
            if (Min == 60) {
                Min = 0;
                Hour++;
            }
            if (Sec == 60) {
                Sec = 0;
                Min++;
            }

            lastTime = std::chrono::steady_clock::now();           
            Changed = true; 
        }

    }
}
