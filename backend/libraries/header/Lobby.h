#pragma once

#include <string>
#include <list>

#include "User.h"

/// @brief Represents a lobby which players can create and join to
class Lobby
{
public:
    /// @brief Various answers the lobby can give when calling methods
    enum LobbyResult
    {
        Success2,
        UserAlreadyInLobby,
        LobbyFull,
        LobbyDoesNotExist,
        UserNotInLobby
    };

    /// @brief Maximum amount of users that can be in the lobby
    int maxUsers;

    /// @brief This lobby's unique id
    std::string lobbyId;

    /// @brief A list containig users that are in the lobby
    std::list<User> lobbyUsers;
    
    /// @brief Constructor
    Lobby();

    /// @brief Adds the selected user to the lobby
    /// @param user User object to be added to the lobby
    /// @return Information about the result of adding the user
    LobbyResult AddUser(User user);

    /// @brief Checks wheather the user is in this lobby
    /// @param userId Unique id of the user
    /// @return True if the user is in the lobby, false otherwise
    bool CheckUserInLobby(std::string userId);

    /// @brief Removes the user from this lobby
    /// @param userId Unique id of the user
    /// @return The result of removing
    LobbyResult RemoveUser(std::string userId);

    /// @brief Method counts how many users are in the lobby
    /// @return Amount of users in the lobby
    int GetUserCount();
};