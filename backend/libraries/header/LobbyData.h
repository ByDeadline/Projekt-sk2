#pragma once

#include <string>

#include "IRequestData.h"

/// @brief Represents data sent from the client to lobby
class LobbyData : public IRequestData
{
public:
    /// @brief User's id
    std::string userId;
    
    /// @brief Lobby's unique id
    std::string lobbyId;

    /// @brief Player's progress in a game
    std::string progress;
};