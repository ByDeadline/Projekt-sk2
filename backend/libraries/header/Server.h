#pragma once

#include <netinet/in.h>
#include <list>
#include <memory>

#include <ServerConnection.h>
#include <IRequestResult.h>
#include <IRequestData.h>
#include <User.h>

/// @brief A class that gives requests to other clasess and accepts them and gives it to the handler
class Server
{
private:

    /// @brief Represents the current id that a new user will recive
    static int idCounter;
    
    static std::list<std::shared_ptr<ServerConnection>> serverConnections;
public:

    static std::list<std::shared_ptr<ServerConnection>> GetServerConnections();

    static std::shared_ptr<User> GetUserById(int clientId);

    static std::shared_ptr<ServerConnection> AddServerConnection(sockaddr_in clientAddress);

    static std::shared_ptr<ServerConnection> AddServerConnection(sockaddr_in clientAddress, std::shared_ptr<User> user);

    static bool addUserToConnection(int id, std::shared_ptr<User> user);

    static std::shared_ptr<IRequestResult> ReciveRequest(std::shared_ptr<IRequestData> requestData);
};