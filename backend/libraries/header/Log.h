#pragma once

#include <string>

/// @brief Log's the information happenig in the server
class Log
{
public:
    /// @brief Logs' the chosen text
    /// @param text Text to be logged
    static void Write(std::string text);
};