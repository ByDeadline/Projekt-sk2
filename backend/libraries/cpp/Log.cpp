#include <iostream>
#include <fstream>
#include <string>

#include "../header/Log.h"
#include "../header/Config.h"

void Log::Write(std::string text)
{
    if (Config::writeToConsole)
    {
        std::cout << text << std::endl;
    }

    if (Config::writeToFile)
    {
        Config::logFile << text << std::endl;
    }
}
