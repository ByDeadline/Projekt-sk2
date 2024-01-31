#include <iostream>
#include <fstream>
#include <string>

#include "../header/Log.h"

void Log::Write(std::string text)
{
    std::cout << text << std::endl;
}
