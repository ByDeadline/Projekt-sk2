#include <netinet/in.h>
#include <list>
#include <memory>

#include "../header/ServerConnection.h"
#include "../header/Server.h"
#include "../header/UserHandler.h"
#include "../header/Log.h"
#include "../header/LobbyHandler.h"

int Server::idCounter = 0;
std::list<std::shared_ptr<ServerConnection>> Server::serverConnections;

std::list<std::shared_ptr<ServerConnection>> Server::GetServerConnections()
{
    return Server::serverConnections;
}

std::shared_ptr<User> Server::GetUserById(int clientId)
{
    for (auto connection : Server::serverConnections)
    {
        if (connection->clientId == clientId)
            return connection->user;
    }

    return nullptr;
}

void Server::RemoveUserById(int clientId)
{
    for (auto connection : Server::serverConnections)
    {
        if (connection->clientId == clientId)
            return connection->user.reset();
    }
}

std::shared_ptr<ServerConnection> Server::AddServerConnection(sockaddr_in clientAddress)
{
    auto serverConnection = std::make_shared<ServerConnection>();
    serverConnection->clientId = Server::idCounter++;
    serverConnection->clientAddress = clientAddress;
    serverConnection->connected = true;
    Server::serverConnections.push_back(serverConnection);

    return serverConnection;
}

std::shared_ptr<ServerConnection> Server::AddServerConnection(sockaddr_in clientAddress, std::shared_ptr<User> user)
{
    std::shared_ptr<ServerConnection> serverConnection;
    serverConnection->clientId = Server::idCounter++;
    serverConnection->clientAddress = clientAddress;
    serverConnection->user = user;
    Server::serverConnections.push_back(serverConnection);

    return serverConnection;
}

bool Server::AddUserToConnection(int id, std::shared_ptr<User> user)
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

std::shared_ptr<IRequestResult> Server::ReciveRequest(std::shared_ptr<IRequestData> requestData)
{
    switch (requestData->GetRequestType())
    {
        case RequestType::UserLogin:
            Log::Write(std::to_string(requestData->clientId) + ": Server recognised the request for creating a user");
            return UserHandler::HandleLogin(requestData);
        case RequestType::UserLogout:
            Log::Write(std::to_string(requestData->clientId) + ": Server recognised the request for loging out");
            return UserHandler::HandleLogout(requestData);
        case RequestType::CreateLobby:
            Log::Write(std::to_string(requestData->clientId) + ": Server recognised the request for creating a lobby");
            return LobbyHandler::HandleCreateLobby(requestData);
        case RequestType::ShowLobbies:
            Log::Write(std::to_string(requestData->clientId) + ": Server recognised the request for showing all lobbies");
            return LobbyHandler::HandleShowLobbies(requestData);
    }

    Log::Write(std::to_string(requestData->clientId) + "Server did not recognise the request");
    auto result = std::make_shared<IRequestResult>();
    return result;
}