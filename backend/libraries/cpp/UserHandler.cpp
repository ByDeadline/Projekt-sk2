#include <memory>
#include <string>

#include "../header/UserHandler.h"
#include "../header/UserData.h"
#include "../header/User.h"
#include "../header/IRequestResult.h"
#include "../header/Log.h"
#include "../header/Server.h"

int UserHandler::idCounter = 0;
std::list<std::shared_ptr<User>> UserHandler::users;

std::shared_ptr<User> UserHandler::GetUserByUsername(std::string username)
{
    for (auto user : UserHandler::users)
    {
        if (user->username == username)
        {
            return std::make_shared<User>(*user);
        }
    }

    return nullptr;
}

std::shared_ptr<User> UserHandler::GetUserByUserId(std::string userId)
{
    for (auto user : UserHandler::users)
    {
        if (user->id == userId)
        {
            return std::make_shared<User>(*user);
        }
    }

    return nullptr;
}

std::string UserHandler::AddUser(std::string username, int clientId)
{
    auto user = std::make_shared<User>();
    user->username = username;
    user->id = "#" + std::to_string(UserHandler::idCounter++);
    UserHandler::users.push_back(user);
    Server::AddUserToConnection(clientId, user);

    return user->id;
}

void UserHandler::RemoveUser(std::string userId, int clientId)
{
    for (auto user : UserHandler::users)
    {
        if (user->id == userId)
        {
            UserHandler::users.remove(user);
            Server::RemoveUserById(clientId);
            return;
        }
    }
}

std::shared_ptr<IRequestResult> UserHandler::HandleLogin(std::shared_ptr<IRequestData> requestData)
{
    auto userData = std::make_shared<UserData>(*dynamic_cast<UserData*>(requestData.get()));
    auto userActionResult = std::make_shared<UserActionResult>();

    if (Server::GetUserById(userData->clientId) != nullptr)
    {
        userActionResult->resultType = UserActionResult::ResultTypeEnum::ClientAlreadyLoggedIn;
        Log::Write(std::to_string(userData->clientId) + ": error: This client is already logged in");

        return userActionResult;
    }

    if (UserHandler::GetUserByUsername(userData->username) == nullptr)
    {
        std::string userId = UserHandler::AddUser(userData->username, userData->clientId);
        userActionResult->resultType = UserActionResult::ResultTypeEnum::Success;
        userActionResult->setUniqueCode(userId);
        Log::Write(std::to_string(userData->clientId) + ": Successfully logged in user " + userData->username + userId);
        
        return userActionResult;
    }

    Log::Write(std::to_string(userData->clientId) + ": error: Username " + userData->username + " already exists");
    userActionResult->resultType = UserActionResult::ResultTypeEnum::UsernameAlreadyExists;
    return userActionResult;
}

std::shared_ptr<IRequestResult> UserHandler::HandleLogout(std::shared_ptr<IRequestData> requestData)
{
    auto userData = std::make_shared<UserData>(*dynamic_cast<UserData*>(requestData.get()));
    auto userActionResult = std::make_shared<UserActionResult>();

    auto user = UserHandler::GetUserByUserId(userData->username);
    if (user != nullptr)
    {
        UserHandler::RemoveUser(user->id, userData->clientId);
        userActionResult->resultType = UserActionResult::ResultTypeEnum::Success;
        userActionResult->setUniqueCode(userData->username);

        Log::Write(std::to_string(userData->clientId) + ": Successfully logged out user " + userData->username);
        return userActionResult;
    }

    Log::Write(std::to_string(userData->clientId) + ": error: User already logged in or wrong id provided");
    userActionResult->resultType = UserActionResult::ResultTypeEnum::WrongIdOrNotLoggedIn;
    return userActionResult;
}