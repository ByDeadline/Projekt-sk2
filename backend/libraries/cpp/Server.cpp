#include <netinet/in.h>
#include <list>
#include <memory>

#include <ServerConnection.h>
#include <Server.h>

int Server::idCounter = 0;

std::list<std::shared_ptr<ServerConnection>> Server::getServerConnections()
{
    return Server::serverConnections;
}

std::shared_ptr<ServerConnection> Server::addServerConnection(sockaddr_in clientAddress)
{
    std::shared_ptr<ServerConnection> serverConnection;
    serverConnection->clientId = Server::idCounter++;
    serverConnection->clientAddress = clientAddress;
    Server::serverConnections.push_back(serverConnection);

    return serverConnection;
}

std::shared_ptr<ServerConnection> Server::addServerConnection(sockaddr_in clientAddress, std::shared_ptr<User> user)
{
    std::shared_ptr<ServerConnection> serverConnection;
    serverConnection->clientId = Server::idCounter++;
    serverConnection->clientAddress = clientAddress;
    serverConnection->user = user;
    Server::serverConnections.push_back(serverConnection);

    return serverConnection;
}

bool Server::addUserToConnection(int id, std::shared_ptr<User> user)
{
    for (auto serverConnection : Server::serverConnections)
    {
        if (serverConnection->clientId == id)
        {
            serverConnection->user = user;
            return true;
        }
    }
    
    return false;
}