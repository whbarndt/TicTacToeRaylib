#pragma once

// My Time class; used for input handeling but also 
class Time
{
public:
    float timeSinceWindowStart = .0f;
    float timeSinceLastFrame = .0f; // A.K.A. deltaTim

    void UpdateTime();

    Time();
    ~Time();
};