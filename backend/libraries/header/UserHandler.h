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
    static std::shared_ptr<User> GetUser(std::string username);
    static std::string AddUser(std::string username);
    static std::shared_ptr<IRequestResult> HandleLogin(std::shared_ptr<IRequestData> requestData);
};