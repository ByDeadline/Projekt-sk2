#pragma once

#include <string>

/// @brief A static class that stores basic global settings for the whole application
class GlobalSettings
{
public:
    /// @brief Server port for TCP/UDP
    static int ServerPort;

    /// @brief Max clients for TCP listen
    static const int TCPSocketMaxRequests = 100;

    /// @brief Max number of characters to be read from a TCP socket
    static const int TCPMaxCharReadLength = 256;

    /// @brief Max length of address
    static const int MaxCharAddressLength = 256;

    /// @brief Time in ms after which the TCP server timeouts
    static const int TCPUserConnectionTimeout = 30000;
  
    /// @brief Max users that can be in one lobby
    static const int LobbyMaxUsers = 4;

    /// @brief Amount of empty requests that can be tolerated
    static const int UselessRequestLimit = 10;
};
