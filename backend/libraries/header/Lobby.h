#pragma once

#include <string>
#include <list>

#include "User.h"
#include "Player.h"
#include "Game.h"

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
        UserNotInLobby,
        GameInProgress
    };

    /// @brief Maximum amount of users that can be in the lobby
    int maxUsers;

    /// @brief This lobby's unique id
    std::string lobbyId;

    /// @brief A list containig users that are in the lobby
    std::list<Player> lobbyUsers;

    /// @brief A flag that determines whethere a game is in progress
    bool gameInProgress = false;

    std::shared_ptr<Game> game;
    
    /// @brief Constructor
    Lobby();

    void SendLobbyStatus();

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
    /// @param forceRemove Decides to remove user even though he is in a game
    /// @return The result of removing
    LobbyResult RemoveUser(std::string userId, bool forceRemove = false);

    /// @brief Sets the selected user as ready
    /// @param userId Unique id of the user
    /// @return The result of setting ready
    LobbyResult SetUserReady(std::string userId);

    /// @brief Starts the game assigned to this lobby
    void StartGame();

    /// @brief Method checks if all users are set as ready
    /// @return True if user is ready, false otherwise
    bool CheckAllUsersReady();

    /// @brief Method counts how many users are in the lobby
    /// @return Amount of users in the lobby
    int GetUserCount();
};