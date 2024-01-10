#pragma once

/// @brief A static class that stores basic global settings for the whole application
class GlobalSettings
{
public:
    /// @brief Server port for TCP/UDP
    static const int ServerPort = 1234;

    /// @brief Max clients for TCP listen
    static const int TCPSocketMaxRequests = 100;

    /// @brief Max number of characters to be read from a TCP socket
    static const int TCPMaxCharReadLength = 256;

    static const int MaxCharAddressLength = 256;

    /// @brief Time in ms after which the TCP server timeouts
    static const int TCPUserConnectionTimeout = 30000;
};