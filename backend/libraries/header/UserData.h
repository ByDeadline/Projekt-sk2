#pragma once

#include <string>

#include <IRequestData.h>

/// @brief Represents data from the client to a user
class UserData : public IRequestData
{
public:
    /// @brief User's id
    std::string userId;

    /// @brief Username
    std::string username;

    /// @brief Id of the user to be deleted
    std::string userToDelete;

    /// @brief Is the user an admin
    bool admin = false;
};