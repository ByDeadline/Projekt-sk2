#pragma once

#include <filesystem>
#include <iostream>
#include <istream>

class Config
{
public:
    static std::filesystem::path configFilePath;
    static std::filesystem::path logPath;

    static std::ofstream logFile;
    static std::fstream configFile;

    static bool writeToFile;
    static bool writeToConsole;

    static void setUpLog();
    static void updateSettings();
};
