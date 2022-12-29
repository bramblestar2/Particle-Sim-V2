#include "Clock.h"

Clock::Clock()
{
    time = glfwGetTime();
}

float Clock::getElapsedTime()
{
    return glfwGetTime() - time;
}

float Clock::reset()
{
    float temp = getElapsedTime();
    time = glfwGetTime();
    return temp;
}
