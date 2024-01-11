#pragma once

#include <map>
#include <string>

#include "../header/IRequestResult.h"

class UserActionResult : public IRequestResult
{
public:
    enum ResultTypeEnum
    {
        Success,
        UsernameAlreadyExists,
        ClientAlreadyLoggedIn,
        WrongIdOrNotLoggedIn
    };
    ResultTypeEnum resultType;
    std::string GetMessage() override { return this->resultTypeMessages[this->resultType]; }

    std::string uniqueCode;
private:
    std::map<ResultTypeEnum, std::string> resultTypeMessages
    {
        { ResultTypeEnum::Success, "Successfuly added the user" },
        { ResultTypeEnum::UsernameAlreadyExists, "A user with the same nickname already exists" },
        { ResultTypeEnum::ClientAlreadyLoggedIn, "Client is already logged in" },
        { ResultTypeEnum::WrongIdOrNotLoggedIn, "Given Id is incorrect or the user is not logged in" }
    };
};