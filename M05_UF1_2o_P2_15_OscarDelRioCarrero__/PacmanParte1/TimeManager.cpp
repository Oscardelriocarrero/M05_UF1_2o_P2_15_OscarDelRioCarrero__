#include "TimeManager.h"

TimeManager& TimeManager::getInstance()
{
    static TimeManager instance;
    return instance;
}

void TimeManager::NextFrame()
{
    auto elapsed = (std::chrono::high_resolution_clock::now() - start);
    deltaTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() / 1000;
    framecount++;
    time += deltaTime;
    start = std::chrono::high_resolution_clock::now();
}
