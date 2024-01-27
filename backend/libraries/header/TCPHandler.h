#pragma once

#include <memory>

#include <IServerRequestHandler.h>
#include "IRequestResult.h"
#include "ServerConnection.h"

/// @brief A class that uses sockets to communicate with clients using TCP
class TCPHandler : public IServerRequestHandler
{
private:
    /// @brief A method that listens for new clients
    void ListenForClinets();

    /// @brief A method that handles an established connection with a client. Must be called Async
    /// @param fd A socket to the client connection
    /// @param clientAddress A struct containing client's address
    static void HandleConnectionAsync(int fd, sockaddr_in clientAddress);

public:
    /// @brief A constructor that starts the TCP server connection
    TCPHandler();

    /// @brief Sends a message using a socket in the serverConnection
    /// @param serverConnection Server connection of a client that the message is meant to be sent
    /// @param requestResult Data containing information to be sent to the user
    static void SendWithFd(std::shared_ptr<ServerConnection> serverConnection, std::shared_ptr<IRequestResult> requestResult);
};