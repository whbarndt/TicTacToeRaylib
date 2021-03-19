#include "raylib.h"
#include "TTTTime.hpp"

Time::Time() {};
Time::~Time() {};

void Time::UpdateTime()
{
    timeSinceLastFrame = GetFrameTime();
    timeSinceWindowStart = GetTime();
};