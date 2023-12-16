#pragma once

#include <netinet/in.h>
#include <list>
#include <memory>

#include <ServerConnection.h>

class Server
{
private:
    static int idCounter;
    static std::list<std::shared_ptr<ServerConnection>> serverConnections;

public:
    static std::list<std::shared_ptr<ServerConnection>> getServerConnections();
    static std::shared_ptr<ServerConnection> addServerConnection(sockaddr_in clientAddress);
    static std::shared_ptr<ServerConnection> addServerConnection(sockaddr_in clientAddress, std::shared_ptr<User> user);
    static bool addUserToConnection(int id, std::shared_ptr<User> user);
};