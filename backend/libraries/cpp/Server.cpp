#include <netinet/in.h>
#include <list>
#include <memory>

#include "../header/ServerConnection.h"
#include "../header/Server.h"
#include "../header/UserHandler.h"
#include "../header/Log.h"

int Server::idCounter = 0;
std::list<std::shared_ptr<ServerConnection>> Server::serverConnections;

std::list<std::shared_ptr<ServerConnection>> Server::getServerConnections()
{
    return Server::serverConnections;
}

std::shared_ptr<ServerConnection> Server::addServerConnection(sockaddr_in clientAddress)
{
    auto serverConnection = std::make_shared<ServerConnection>();
    serverConnection->clientId = Server::idCounter++;
    serverConnection->clientAddress = clientAddress;
    serverConnection->connected = true;
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

IRequestResult Server::ReciveRequest(IRequestData requestData)
{
    switch (requestData.GetRequestType())
    {
        case RequestType::UserLogin:
            Log::Write("Server recognised the request for creating a user");
            return UserHandler::HandleLogin(requestData);
    }

    Log::Write("Server did not recognise the request");
    IRequestResult result;
    result.resultConclusion = ResultType::Unknown1;
    return result;
}