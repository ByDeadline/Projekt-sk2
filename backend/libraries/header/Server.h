#pragma once

#include <netinet/in.h>
#include <list>
#include <memory>

#include <ServerConnection.h>
#include <IRequestResult.h>
#include <IRequestData.h>
#include <User.h>
#include <Player.h>

/// @brief A class that gives requests to other clasess and accepts them and gives it to the handler
class Server
{
private:

    /// @brief Represents the current id that a new user will recive
    static int idCounter;
    
    /// @brief List of pointers containging a server connection of a client
    static std::list<std::shared_ptr<ServerConnection>> serverConnections;
public:
    /// @brief Gets a list of pointers containging a server connection of a client
    /// @return List of pointers containging a server connection of a client
    static std::list<std::shared_ptr<ServerConnection>> GetServerConnections();

    static std::shared_ptr<ServerConnection> GetServerConnectionByUserId(std::string userId);

    static std::shared_ptr<ServerConnection> GetServerConnectionByClientId(int clientId);

    static void DisconnectClient(int clientId);

    static void RemoveServerConnection(int clientId);

    /// @brief Finds a user based on client's connection id
    /// @param clientId Client's connection id
    /// @return Pointer to a user or nullptr if not found
    static std::shared_ptr<User> GetUserById(int clientId);

    /// @brief Removes the user from connections. However it does not disconnect the client
    /// @param clientId Client's connection id
    static void RemoveUserByUserId(std::string userId);

    /// @brief Adds a new server connection
    /// @param clientAddress Address of the client
    /// @return Pointer to a new server connection
    static std::shared_ptr<ServerConnection> AddServerConnection(sockaddr_in clientAddress, int fd);

    /// @brief Adds a new server connection
    /// @param clientAddress Address of the client
    /// @param user User to be added to the connection
    /// @return Pointer to a new server connection
    static std::shared_ptr<ServerConnection> AddServerConnection(sockaddr_in clientAddress, int fd, std::shared_ptr<User> user);

    /// @brief Adds a user to the connection
    /// @param id Client's connection id
    /// @param user Pointer to a user object to be added
    /// @return True if added successfully, false otherwise
    static bool AddUserToConnection(int id, std::shared_ptr<User> user);

    /// @brief Recives and redirects a request sent by a client to a correct handler
    /// @param requestData Data sent by the client
    /// @return Request result the handler provided
    static std::shared_ptr<IRequestResult> ReciveRequest(std::shared_ptr<IRequestData> requestData);

    /// @brief Sends information to a list of users
    /// @param users List of users
    /// @param requestResult Data to be sent
    static void Send(std::list<Player> users, std::shared_ptr<IRequestResult> requestResult);
};