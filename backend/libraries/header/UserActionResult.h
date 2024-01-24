#pragma once

#include <map>
#include <string>

#include "../header/IRequestResult.h"

/// @brief Holds information to be sent to the client about the request that was made to User
class UserActionResult : public IRequestResult
{
public:
    /// @brief Represents different type of answers
    enum ResultTypeEnum
    {
        Success,
        UsernameAlreadyExists,
        ClientAlreadyLoggedIn,
        WrongIdOrNotLoggedIn,
        AliveOk,
        UserStatistics,
        NoPrivilages
    };
    ResultTypeEnum resultType;

    struct UserStats
    {
        std::string username;
        std::string lobbyname;
        std::string ingame;
    };
    

    /// @brief Gets the message to be sent to the user based on the set result type
    /// @return Message to be sent to user
    std::string GetMessage() override { return this->resultTypeMessages[this->resultType]; }

    /// @brief Sets the unique code
    /// @param lobbyId Unique code
    void setUniqueCode(std::string uniqueCode) { this->uniqueCode = uniqueCode; this->CreateResultTypeMessage(); }

    /// @brief Sets the user statistics to a text
    /// @param lobbies Logged in users
    void setUserStats(std::list<UserStats> userStats) { 
        this->userStats = "";
        for (auto userStat : userStats)
        {
            this->userStats += userStat.username + "," + userStat.lobbyname + "," + userStat.ingame + '\n';
        }

        this->CreateResultTypeMessage();
    }

    /// @brief Constructor creates the message
    UserActionResult() { this->CreateResultTypeMessage(); }
private:
    /// @brief Unique code of the user
    std::string uniqueCode;

    std::string userStats;

    /// @brief A dictionary holding a text to be sent to the user based on the set result type
    std::map<ResultTypeEnum, std::string> resultTypeMessages;

    /// @brief Constructs the dictionary holding a text to be sent to the user based on the set result type
    void CreateResultTypeMessage() { 
        resultTypeMessages =
        {
            { ResultTypeEnum::Success, "success," + this->uniqueCode },
            { ResultTypeEnum::UsernameAlreadyExists, "failed,A user with the same nickname already exists" },
            { ResultTypeEnum::ClientAlreadyLoggedIn, "failed,Client is already logged in" },
            { ResultTypeEnum::WrongIdOrNotLoggedIn, "failed,Given Id is incorrect or the user is not logged in" },
            { ResultTypeEnum::AliveOk, "ok" },
            { ResultTypeEnum::NoPrivilages, "failed,No privilages" },
            { ResultTypeEnum::UserStatistics, "success," + this->userStats }
        };
    };
};