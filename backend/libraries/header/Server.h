#pragma once

#include <netinet/in.h>
#include <list>
#include <memory>

#include <ServerConnection.h>
#include <IRequestResult.h>
#include <IRequestData.h>

/// @brief A class that gives requests to other clasess and accepts them and gives it to the handler
class Server
{
private:

    /// @brief Represents the current id that a new user will recive
    static int idCounter;
    
    static std::list<std::shared_ptr<ServerConnection>> serverConnections;
public:

    static std::list<std::shared_ptr<ServerConnection>> getServerConnections();

    static std::shared_ptr<ServerConnection> addServerConnection(sockaddr_in clientAddress);

    static std::shared_ptr<ServerConnection> addServerConnection(sockaddr_in clientAddress, std::shared_ptr<User> user);

    static bool addUserToConnection(int id, std::shared_ptr<User> user);

    static IRequestResult ReciveRequest(IRequestData requestData);
};