#pragma once

#include <iostream>
#include <string>


void Fatal(std::string message)
{
    std::cout << message << std::endl;
    std::terminate();
}

