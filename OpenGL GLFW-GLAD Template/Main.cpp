//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <iostream>

#include "Simulation.h"

int main()
{
    Simulation sim;

    sim.run();

    return 0;
}
