#pragma once

#include <map>
#include <string>

/// @brief An interface for classes that store information to be sent to the client from server
class IRequestResult
{
public:
    /// @brief Method that creates the message to be sent to the client
    /// @return Message to be sent to the client
    virtual std::string GetMessage() { return "unknown error"; }
};