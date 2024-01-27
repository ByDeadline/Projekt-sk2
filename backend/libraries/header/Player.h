#pragma once

#include "User.h"

/// @brief Defines a player
class Player : public User
{
public:
    /// @brief Is the player ready in the lobby
    bool isReady = false;

    /// @brief Progress of the player in the game
    int progress = 0;
};