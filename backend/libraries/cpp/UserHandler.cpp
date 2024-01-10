#include <memory>
#include <string>

#include "../header/UserHandler.h"
#include "../header/UserData.h"
#include "../header/User.h"
#include "../header/IRequestResult.h"
#include "../header/ResultType.h"
#include "../header/Log.h"

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

std::string UserHandler::AddUser(std::string username)
{
    auto user = std::make_shared<User>();
    user->username = username;
    user->id = "#" + std::to_string(UserHandler::idCounter++);
    UserHandler::users.push_back(user);

    return user->id;
}

UserActionResult UserHandler::HandleLogin(IRequestData requestData)
{
    std::shared_ptr<UserData> userData(dynamic_cast<UserData*>(&requestData));
    UserActionResult userActionResult;
    userActionResult.resultConclusion = ResultType::AddUser;

    if (UserHandler::GetUser(userData->username) == nullptr)
    {
        std::string userId = UserHandler::AddUser(userData->username);
        userActionResult.resultType = UserActionResult::ResultTypeEnum::Success;
        Log::Write("Successfully added user " + userData->username + userId);
        
        return userActionResult;
    }

    Log::Write("Error: Username " + userData->username + " already exists");
    userActionResult.resultType = UserActionResult::ResultTypeEnum::UsernameAlreadyExists;
    return userActionResult;
}