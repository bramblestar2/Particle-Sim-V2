#include "Joystick.h"

bool Joystick::isConnected(int _Joystick)
{
    return glfwJoystickPresent(_Joystick) == 1 ? true : false;
}

int Joystick::getButtonCount(int _Joystick)
{
    int count;
    glfwGetJoystickButtons(_Joystick, &count);
    return count;
}