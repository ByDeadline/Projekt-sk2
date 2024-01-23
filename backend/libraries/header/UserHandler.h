#pragma once

#include <memory>
#include <list>
#include <string>

#include <UserData.h>
#include <UserActionResult.h>
#include <IRequestData.h>
#include <User.h>

/// @brief Handles request about user stuff
class UserHandler
{
private:
    /// @brief Unique id that a new user will recive
    static int idCounter;

    /// @brief List of pointers holding users
    static std::list<std::shared_ptr<User>> users;

public:
    /// @brief Finds a user by the username
    /// @param username Username of the user to be found
    /// @return Found user or nullptr if not found
    static std::shared_ptr<User> GetUserByUsername(std::string username);

    /// @brief Finds a user by user's unique id
    /// @param userId Id of the user to found
    /// @return Found user or nullptr if not found
    static std::shared_ptr<User> GetUserByUserId(std::string userId);

    /// @brief Creates and adds a new user with the selected username
    /// @param username Desired username
    /// @param clientId Id of client' connection
    /// @param isAdmin Is the user supposed to an admin 
    /// @return Created user's unique id
    static std::string AddUser(std::string username, int clientId, bool isAdmin);

    /// @brief Removes the user with the specifed unique user's id
    /// @param userId User's unique id
    /// @param clientId Client's connection unique id
    static void RemoveUser(std::string userId);

    /// @brief Handles the request for logging in
    /// @param requestData Data sent by the client
    /// @return Result of the request
    static std::shared_ptr<IRequestResult> HandleLogin(std::shared_ptr<IRequestData> requestData);

    /// @brief Handles the request for logging out
    /// @param requestData Data sent by the client
    /// @return Result of the request
    static std::shared_ptr<IRequestResult> HandleLogout(std::shared_ptr<IRequestData> requestData);

    /// @brief Handles the request for removing a selected user by force. Only admin can do that
    /// @param requestData Data sent by the client
    /// @return Result of the request
    static std::shared_ptr<IRequestResult> HandleRemoveUser(std::shared_ptr<IRequestData> requestData);

    static std::shared_ptr<IRequestResult> HandleAlive(std::shared_ptr<IRequestData> requestData);
};