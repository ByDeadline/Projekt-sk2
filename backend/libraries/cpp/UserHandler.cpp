#include <memory>
#include <string>

#include "../header/UserHandler.h"
#include "../header/UserData.h"
#include "../header/User.h"
#include "../header/IRequestResult.h"
#include "../header/Log.h"
#include "../header/Server.h"
#include "../header/LobbyHandler.h"

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

std::string UserHandler::AddUser(std::string username, int clientId, bool isAdmin)
{
    auto user = std::make_shared<User>();
    user->username = username;
    user->id = "#" + std::to_string(UserHandler::idCounter++);
    user->admin = isAdmin;
    UserHandler::users.push_back(user);
    Server::AddUserToConnection(clientId, user);

    return user->id;
}

void UserHandler::RemoveUser(std::string userId)
{
    LobbyHandler::RemoveUserFromLobby(userId);

    UserHandler::users.remove_if([=](std::shared_ptr<User> user) { return user->id == userId; });
    Server::RemoveUserByUserId(userId);
}

std::list<UserActionResult::UserStats> UserHandler::BuildUserStats()
{
    std::list<UserActionResult::UserStats> userStats;
    for (auto user : UserHandler::users)
    {
        UserActionResult::UserStats userStat;
        
        userStat.username = user->username;
        
        auto lobby = LobbyHandler::CheckUserInAnyLobby(user->id);
        userStat.lobbyname = lobby != nullptr ? lobby->lobbyId : "None";

        userStat.ingame = "No";
        if (lobby != nullptr)
        {
            userStat.ingame = lobby->gameInProgress ? "Yes" : "No";
        }

        userStats.push_back(userStat);
    }

    return userStats;
}

std::shared_ptr<IRequestResult> UserHandler::HandleShowUsers(std::shared_ptr<IRequestData> requestData)
{
    auto userData = std::make_shared<UserData>(*dynamic_cast<UserData*>(requestData.get()));
    auto userActionResult = std::make_shared<UserActionResult>();

    auto user = UserHandler::GetUserByUserId(userData->userId);
    if (user != nullptr)
    {
        if (user->admin)
        {
            userActionResult->setUserStats(UserHandler::BuildUserStats());
            userActionResult->resultType = UserActionResult::ResultTypeEnum::UserStatistics;
            return userActionResult;
        }

        userActionResult->resultType = UserActionResult::ResultTypeEnum::NoPrivilages;
        return userActionResult;
    }

    Log::Write(std::to_string(userData->clientId) + ": error: User not logged in");
    userActionResult->resultType = UserActionResult::ResultTypeEnum::WrongIdOrNotLoggedIn;
    return userActionResult;
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
        std::string userId = UserHandler::AddUser(userData->username, userData->clientId, userData->admin);
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

    auto user = UserHandler::GetUserByUserId(userData->userId);
    if (user != nullptr)
    {
        UserHandler::RemoveUser(user->id);
        userActionResult->resultType = UserActionResult::ResultTypeEnum::Success;
        userActionResult->setUniqueCode(userData->username);

        Log::Write(std::to_string(userData->clientId) + ": Successfully logged out user " + userData->username);
        return userActionResult;
    }

    Log::Write(std::to_string(userData->clientId) + ": error: User already logged in or wrong id provided");
    userActionResult->resultType = UserActionResult::ResultTypeEnum::WrongIdOrNotLoggedIn;
    return userActionResult;
}

std::shared_ptr<IRequestResult> UserHandler::HandleRemoveUser(std::shared_ptr<IRequestData> requestData)
{
    auto userData = std::make_shared<UserData>(*dynamic_cast<UserData*>(requestData.get()));
    auto userActionResult = std::make_shared<UserActionResult>();

    auto user = UserHandler::GetUserByUserId(userData->userId);
    if (user != nullptr)
    {
        if (user->admin)
        {
            UserHandler::RemoveUser(userData->userToDelete);
            userActionResult->resultType = UserActionResult::ResultTypeEnum::Success;
            userActionResult->setUniqueCode(userData->userToDelete);
            return userActionResult;
        }

        userActionResult->resultType = UserActionResult::ResultTypeEnum::NoPrivilages;
        return userActionResult;
    }

    Log::Write(std::to_string(userData->clientId) + ": error: User already logged in or wrong id provided");
    userActionResult->resultType = UserActionResult::ResultTypeEnum::WrongIdOrNotLoggedIn;
    return userActionResult;
}

std::shared_ptr<IRequestResult> UserHandler::HandleAlive(std::shared_ptr<IRequestData> requestData)
{
    return nullptr;
}