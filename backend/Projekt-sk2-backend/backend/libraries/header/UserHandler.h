#pragma once

#include <memory>
#include <list>
#include <string>

#include <UserData.h>
#include <UserActionResult.h>
#include <IRequestData.h>
#include <User.h>

class UserHandler
{
private:
    static int idCounter;
    static std::list<std::shared_ptr<User>> users;

public:
    static std::shared_ptr<User> GetUserByUsername(std::string username);
    static std::shared_ptr<User> GetUserByUserId(std::string userId);
    static std::string AddUser(std::string username, int clientId);
    static void RemoveUser(std::string userId, int clientId);
    static std::shared_ptr<IRequestResult> HandleLogin(std::shared_ptr<IRequestData> requestData);
    static std::shared_ptr<IRequestResult> HandleLogout(std::shared_ptr<IRequestData> requestData);
};