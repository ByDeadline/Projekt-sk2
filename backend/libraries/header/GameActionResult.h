#pragma once

#include <map>
#include <string>
#include <list>

#include "../header/IRequestResult.h"
#include "Player.h"

/// @brief Holds information to be sent to the client about the request that was made to User
class GameActionResult : public IRequestResult
{
public:
    /// @brief Represents different type of answers
    enum ResultTypeEnum
    {
        SendText,
        SendStatus
    };
    ResultTypeEnum resultType;

    /// @brief Gets the message to be sent to the user based on the set result type
    /// @return Message to be sent to user
    std::string GetMessage() override { return this->resultTypeMessages[this->resultType]; }

    /// @brief Sets the text that the players will be typing
    /// @param text Text to be filled by players
    /// @param wordsCount Amount of words in the text
    /// @param players List of players
    void setText(std::string text, int wordsCount, std::list<Player> players) { 
        this->text = std::to_string(wordsCount) + "," + text;
        for (auto player : players)
        {
            this->text += "," + player.username;
        } 
        
        this->CreateResultTypeMessage();
    }

    /// @brief Sets status of players as text
    /// @param players List of players
    void setStatus(std::list<Player> players) { 
        this->status = "";
        for (auto player : players)
        {
            this->status += player.username + "," + std::to_string(player.progress) + '\n';
        }

        this->CreateResultTypeMessage();
    }

    /// @brief Constructor creates the message
    GameActionResult() { this->CreateResultTypeMessage(); }
private:
    /// @brief Text that the users will be typing
    std::string text;

    /// @brief Status of all users as a text
    std::string status;

    /// @brief A dictionary holding a text to be sent to the user based on the set result type
    std::map<ResultTypeEnum, std::string> resultTypeMessages;

    /// @brief Constructs the dictionary holding a text to be sent to the user based on the set result type
    void CreateResultTypeMessage() { 
        resultTypeMessages =
        {
            { ResultTypeEnum::SendText, "text," + this->text },
            { ResultTypeEnum::SendStatus, "status," + this->status }
        };
    };
};