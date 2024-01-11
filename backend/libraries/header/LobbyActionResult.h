#pragma once

#include "../header/IRequestResult.h"

class LobbyActionResult : public IRequestResult
{
public:
    enum ResultTypeEnum
    {
        Success1,
        NotLoggedIn
    };
    ResultTypeEnum resultType;
    std::string GetMessage() override { return this->resultTypeMessages[this->resultType]; }

    std::string lobbyId;
private:
    std::map<ResultTypeEnum, std::string> resultTypeMessages
    {
        { ResultTypeEnum::Success1, "success," + this->lobbyId },
        { ResultTypeEnum::NotLoggedIn, "failed,Cannot create lobby because the user is not logged in" }
    };
};