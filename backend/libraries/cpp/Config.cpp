#include <iostream>
#include <fstream>
#include <string>

#include "../header/Config.h"
#include "../header/GlobalSettings.h"

std::filesystem::path Config::configFilePath = "config.txt";
std::filesystem::path Config::logPath = "./logs";
std::ofstream Config::logFile;
std::fstream Config::configFile;
bool Config::writeToFile = true;
bool Config::writeToConsole = true;

std::size_t number_of_files_in_directory(std::filesystem::path path)
{
    using std::filesystem::directory_iterator;
    return std::distance(directory_iterator(path), directory_iterator{});
}

void Config::setUpLog()
{

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current path is " << currentPath << std::endl;
    
    // Create log directory if it doesn't exist
    if (!std::filesystem::exists(Config::logPath))
    {
        std::filesystem::create_directory(Config::logPath);
    }

    // Create log file
    Config::logFile = std::ofstream(Config::logPath.string() + "/log" + std::to_string(number_of_files_in_directory(Config::logPath)) + ".txt");
}

void Config::updateSettings()
{
    Config::configFile.open(Config::configFilePath);

    if (Config::configFile.is_open())
    {
        std::string line;
        while (std::getline(Config::configFile, line, '\n'))
        {
            std::string key = line.substr(0, line.find('='));
            std::string value = line.substr(line.find('=') + 1, line.length());

            if (key == "logPath")
            {
                Config::logPath = value;
            }
            else if (key == "writeToFile")
            {
                Config::writeToFile = value == "true";
            }
            else if (key == "writeToConsole")
            {
                Config::writeToConsole = value == "true";
            }
            else if (key == "ServerPort")
            {
                GlobalSettings::ServerPort = std::stoi(value);
            }

            std::cout << "Key: " << key << " Value: " << value << std::endl;
        }

        Config::configFile.close();
    }
    else
    {
        std::cout << "Unable to open config file. Creating config file with default values" << std::endl;
        
        // Create config file with default values
        Config::configFile = std::fstream(Config::configFilePath, std::ios::out);
        
        Config::configFile << "logPath=" << Config::logPath << std::endl;
        Config::configFile << "writeToFile=" << (Config::writeToFile ? "true" : "false") << std::endl;
        Config::configFile << "writeToConsole=" << (Config::writeToConsole ? "true" : "false") << std::endl;
        Config::configFile << "ServerPort=" << GlobalSettings::ServerPort << std::endl;

        Config::configFile.close();
    }
}
