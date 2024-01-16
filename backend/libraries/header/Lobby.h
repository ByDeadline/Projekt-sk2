#pragma once

#include <string>
#include <list>

#include "User.h"
#include "Player.h"

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
    std::list<Player> lobbyUsers;
    
    /// @brief Constructor
    Lobby();

    /// @brief Creates a player based on user
    /// @param user A user on which to base the player
    /// @return  A player object based on the user
    Player CreatePlayer(User user);

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

    /// @brief Sets the selected user as ready
    /// @param userId Unique id of the user
    /// @return The result of setting ready
    LobbyResult SetUserReady(std::string userId);

    /// @brief Method checks if all users are set as ready
    /// @return True if user is ready, false otherwise
    bool CheckAllUsersReady();

    /// @brief Method counts how many users are in the lobby
    /// @return Amount of users in the lobby
    int GetUserCount();
};