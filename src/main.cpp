#pragma once
#include <iostream>
#include "Engine.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    Engine engine;
    engine.Initialize();
    engine.Run();
    engine.Shutdown();

    

    return 0;
}