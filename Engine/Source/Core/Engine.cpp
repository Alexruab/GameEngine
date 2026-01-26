#include "Engine.h"
#include <iostream>

using namespace GameEngine;

Engine::Engine() 
{
    std::cout << "initializing GameEngine, version  " << version() << std::endl;
}
