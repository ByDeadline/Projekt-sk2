#pragma once

#include <netinet/in.h>
#include <memory>

#include <User.h>

/// @brief Represents a server connection
class ServerConnection
{
public:
    /// @brief Client's unique connection id
    int clientId;

    /// @brief Struct containing client's address
    sockaddr_in clientAddress;

    /// @brief Pointer to the user associeted with the client
    std::shared_ptr<User> user;

    /// @brief Flag showing if the client is connected
    bool connected;
};