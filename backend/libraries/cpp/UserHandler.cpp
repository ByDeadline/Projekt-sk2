#include <memory>
#include <string>

#include "../header/UserHandler.h"
#include "../header/UserData.h"
#include "../header/User.h"
#include "../header/IRequestResult.h"
#include "../header/ResultType.h"
#include "../header/Log.h"
#include "../header/Server.h"

int UserHandler::idCounter = 0;
std::list<std::shared_ptr<User>> UserHandler::users;

std::shared_ptr<User> UserHandler::GetUser(std::string username)
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

std::string UserHandler::AddUser(std::string username, int clientId)
{
    auto user = std::make_shared<User>();
    user->username = username;
    user->id = "#" + std::to_string(UserHandler::idCounter++);
    UserHandler::users.push_back(user);
    Server::AddUserToConnection(clientId, user);

    return user->id;
}

std::shared_ptr<IRequestResult> UserHandler::HandleLogin(std::shared_ptr<IRequestData> requestData)
{
    auto userData = std::make_shared<UserData>(*dynamic_cast<UserData*>(requestData.get()));
    auto userActionResult = std::make_shared<UserActionResult>();
    userActionResult->resultConclusion = ResultType::AddUser;

    if (Server::GetUserById(userData->clientId) != nullptr)
    {
        userActionResult->resultType = UserActionResult::ResultTypeEnum::ClientAlreadyLoggedIn;
        Log::Write(std::to_string(userData->clientId) + ": error: This client is already logged in");

        return userActionResult;
    }

    if (UserHandler::GetUser(userData->username) == nullptr)
    {
        std::string userId = UserHandler::AddUser(userData->username, userData->clientId);
        userActionResult->resultType = UserActionResult::ResultTypeEnum::Success;
        userActionResult->uniqueCode = userId;
        Log::Write(std::to_string(userData->clientId) + ": Successfully logged in user " + userData->username + userId);
        
        return userActionResult;
    }

    Log::Write(std::to_string(userData->clientId) + ": error: Username " + userData->username + " already exists");
    userActionResult->resultType = UserActionResult::ResultTypeEnum::UsernameAlreadyExists;
    return userActionResult;
}