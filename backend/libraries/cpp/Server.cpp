#include <netinet/in.h>
#include <list>
#include <memory>

#include "../header/ServerConnection.h"
#include "../header/Server.h"
#include "../header/UserHandler.h"
#include "../header/Log.h"
#include "../header/LobbyHandler.h"
#include "../header/TCPHandler.h"

int Server::idCounter = 0;
std::list<std::shared_ptr<ServerConnection>> Server::serverConnections;

std::list<std::shared_ptr<ServerConnection>> Server::GetServerConnections()
{
    return Server::serverConnections;
}

std::shared_ptr<ServerConnection> Server::GetServerConnectionByUserId(std::string userId)
{
    for (auto connection : Server::serverConnections)
    {
        if (connection->user->id == userId)
            return connection;
    }

    return nullptr;
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

std::shared_ptr<ServerConnection> Server::AddServerConnection(sockaddr_in clientAddress, int fd)
{
    auto serverConnection = std::make_shared<ServerConnection>();
    serverConnection->clientId = Server::idCounter++;
    serverConnection->clientAddress = clientAddress;
    serverConnection->connected = true;
    serverConnection->fd = fd;
    Server::serverConnections.push_back(serverConnection);

    return serverConnection;
}

std::shared_ptr<ServerConnection> Server::AddServerConnection(sockaddr_in clientAddress, int fd, std::shared_ptr<User> user)
{
    std::shared_ptr<ServerConnection> serverConnection;
    serverConnection->clientId = Server::idCounter++;
    serverConnection->clientAddress = clientAddress;
    serverConnection->user = user;
    serverConnection->fd = fd;
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
        case RequestType::JoinLobby:
            Log::Write(std::to_string(requestData->clientId) + ": Server recognised the request for joining a lobby");
            return LobbyHandler::HandleJoinLobby(requestData);
        case RequestType::LeaveLobby:
            Log::Write(std::to_string(requestData->clientId) + ": Server recognised the request for leaving a lobby");
            return LobbyHandler::HandleLeaveLobby(requestData);
        case RequestType::SetReady:
            Log::Write(std::to_string(requestData->clientId) + ": Server recognised the request for getting ready");
            return LobbyHandler::HandleReady(requestData);
        case RequestType::GiveProgress:
            Log::Write(std::to_string(requestData->clientId) + ": Server recognised the request for giving progres");
    }

    Log::Write(std::to_string(requestData->clientId) + "Server did not recognise the request");
    auto result = std::make_shared<IRequestResult>();
    return result;
}

void Server::Send(std::list<Player> users, std::shared_ptr<IRequestResult> requestResult)
{
    for (auto user : users)
    {
        TCPHandler::SendWithFd(Server::GetServerConnectionByUserId(user.id), requestResult);
    }
}