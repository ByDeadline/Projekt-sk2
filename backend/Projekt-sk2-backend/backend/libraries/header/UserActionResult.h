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

    void setUniqueCode(std::string uniqueCode) { this->uniqueCode = uniqueCode; this->CreateResultTypeMessage(); }

    UserActionResult() { this->CreateResultTypeMessage(); }
private:
    std::string uniqueCode;
    std::map<ResultTypeEnum, std::string> resultTypeMessages;
    void CreateResultTypeMessage() { 
        resultTypeMessages =
        {
            { ResultTypeEnum::Success, "success," + this->uniqueCode },
            { ResultTypeEnum::UsernameAlreadyExists, "failed,A user with the same nickname already exists" },
            { ResultTypeEnum::ClientAlreadyLoggedIn, "failed,Client is already logged in" },
            { ResultTypeEnum::WrongIdOrNotLoggedIn, "failed,Given Id is incorrect or the user is not logged in" }
        };
    };
};