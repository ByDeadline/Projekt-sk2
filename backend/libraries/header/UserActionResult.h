#pragma once

#include <map>

#include <IRequestResult.h>

class UserActionResult : public IRequestResult
{
public:
    enum ResultTypeEnum
    {
        Success,
        UsernameAlreadyExists
    };
    ResultTypeEnum resultType;

    std::string uniqueCode;

private:
    std::map<ResultTypeEnum, std::string> resultTypeMessages
    {
        { ResultTypeEnum::Success, "Successfuly added the user" },
        { ResultTypeEnum::UsernameAlreadyExists, "A user with the same nickname already exists" }
    };
};