#pragma once

#include <list>
#include <memory>

#include "../header/IRequestResult.h"
#include "../header/Lobby.h"

/// @brief Holds information to be sent to the client about the request that was made to Lobby
class LobbyActionResult : public IRequestResult
{
public:
    /// @brief Represents different type of answers
    enum ResultTypeEnum
    {
        Success1,
        SuccessLobbies,
        NotLoggedIn,
        AlreadyInLobby,
        LobbyFull,
        LobbyNotFound
    };
    ResultTypeEnum resultType;

    /// @brief Gets the message to be sent to the user based on the set result type
    /// @return Message to be sent to user
    std::string GetMessage() override { return this->resultTypeMessages[this->resultType]; }

    /// @brief Sets the lobby id
    /// @param lobbyId Lobby unique id
    void setLobbyId(std::string lobbyId) { this->lobbyId = lobbyId; this->CreateResultTypeMessage(); }

    /// @brief Sets the lobbies to a text
    /// @param lobbies Opened lobbies
    void setLobbies(std::list<std::shared_ptr<Lobby>> lobbies) { 
        this->lobbies = "";
        for (auto lobby : lobbies)
        {
            this->lobbies += lobby->lobbyId + "," + std::to_string(lobby->GetUserCount()) + "," + std::to_string(lobby->maxUsers) + '\n';
        }

        this->CreateResultTypeMessage();
    }

    /// @brief Constructor creates the message
    LobbyActionResult() { this->CreateResultTypeMessage(); }
private:
    /// @brief Lobby unique id
    std::string lobbyId;

    /// @brief A text that holds all the lobbies
    std::string lobbies;

    /// @brief A dictionary holding a text to be sent to the user based on the set result type
    std::map<ResultTypeEnum, std::string> resultTypeMessages;

    /// @brief Constructs the dictionary holding a text to be sent to the user based on the set result type
    void CreateResultTypeMessage() {
        resultTypeMessages =
        {
            { ResultTypeEnum::Success1, "success," + this->lobbyId },
            { ResultTypeEnum::SuccessLobbies, "success," + this->lobbies },
            { ResultTypeEnum::NotLoggedIn, "failed,Cannot create lobby because the user is not logged in" },
            { ResultTypeEnum::AlreadyInLobby, "failed,The user is already in lobby" },
            { ResultTypeEnum::LobbyFull, "failed,This lobby is full" },
            { ResultTypeEnum::LobbyNotFound, "failed,Lobby with this id does not exist" }
        };
    }
};