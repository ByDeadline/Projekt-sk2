#pragma once

#include <string>

#include <IRequestData.h>

/// @brief Represents data from the client to a user
class UserData : public IRequestData
{
public:
    /// @brief Username
    std::string username;
};