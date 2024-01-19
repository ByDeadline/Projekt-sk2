#pragma once

#include <memory>
#include <list>
#include <string>

#include <IRequestData.h>
#include <User.h>
#include "../header/LobbyActionResult.h"
#include "Lobby.h"

/// @brief Handles the requests sent by the client about Lobby stuff
class LobbyHandler
{
private:
    /// @brief A list of pointers holding a lobby
    static std::list<std::shared_ptr<Lobby>> lobbies;

    /// @brief Current id that will be assigned to a new lobby
    static int lobbyIdCounter;

public:
    /// @brief Creates a new lobby
    /// @return Created lobby's id
    static std::string CreateLobby();
    
    /// @brief Attempts to join the user to a selected lobby
    /// @param userId Id of the user to join
    /// @param lobbyId Id of the lobby to be joined
    /// @return Result of joining to a lobby
    static Lobby::LobbyResult JoinLobby(std::string userId, std::string lobbyId);
    
    /// @brief Attempts to get the user ready
    /// @param userId Id of the user to set ready
    /// @param lobbyId Id of the lobby
    /// @return Result of setting ready in lobby
    static Lobby::LobbyResult GetReady(std::string userId, std::string lobbyId);

    /// @brief Finds a lobby based on it's id
    /// @param lobbyId Id of the lobby to be found
    /// @return Found lobby or nullptr if not found
    static std::shared_ptr<Lobby> GetLobbyById(std::string lobbyId);
    
    /// @brief Checks whether the selected user is in any lobby
    /// @param userId Id of the user to be checked
    /// @return Pointer to the lobby the user is in, nullptr otherwise
    static std::shared_ptr<Lobby> CheckUserInAnyLobby(std::string userId);

    /// @brief Removes the user from the lobby if he is in any
    /// @param userId Id of the user
    static void RemoveUserFromLobby(std::string userId);

    /// @brief Starts the game with the players in the lobby. MUST BE CALLED ASYNC
    /// @param lobbyId Id of the lobby to start the game in
    static void AsyncStartGame(std::string lobbyId);

    static std::shared_ptr<IRequestResult> HandleProgressUpdate(std::shared_ptr<IRequestData> requestData);

    /// @brief Checks whether everyone in the lobby is ready and starts the game
    /// @param lobbyId Id of the lobby to be checked
    static void CheckAllReady(std::string lobbyId);

    /// @brief Handles the request for joining a lobby
    /// @param requestData Data sent by the client
    /// @return Result of the request
    static std::shared_ptr<IRequestResult> HandleJoinLobby(std::shared_ptr<IRequestData> requestData);

    /// @brief Handles the request for leaveing a lobby
    /// @param requestData Data sent by the client
    /// @return Result of the request
    static std::shared_ptr<IRequestResult> HandleLeaveLobby(std::shared_ptr<IRequestData> requestData);

    /// @brief Handles the request for creating a lobby
    /// @param requestData Data sent by the client
    /// @return Result of the request
    static std::shared_ptr<IRequestResult> HandleCreateLobby(std::shared_ptr<IRequestData> requestData);

    /// @brief Handles the request for getting ready
    /// @param requestData Data sent by the client
    /// @return Result of the request
    static std::shared_ptr<IRequestResult> HandleReady(std::shared_ptr<IRequestData> requestData);

    /// @brief Handles the request for showing all lobbies
    /// @param requestData Data sent by the client
    /// @return Result of the request
    static std::shared_ptr<IRequestResult> HandleShowLobbies(std::shared_ptr<IRequestData> requestData);

};