#pragma once

#include <list>
#include <memory>

#include "../header/IRequestResult.h"
#include "../header/Lobby.h"

class LobbyActionResult : public IRequestResult
{
public:
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
    std::string GetMessage() override { return this->resultTypeMessages[this->resultType]; }

    void setLobbyId(std::string lobbyId) { this->lobbyId = lobbyId; this->CreateResultTypeMessage(); }
    void setLobbies(std::list<std::shared_ptr<Lobby>> lobbies) { 
        this->lobbies = "";
        for (auto lobby : lobbies)
        {
            this->lobbies += lobby->lobbyId + "," + std::to_string(lobby->GetUserCount()) + "," + std::to_string(lobby->maxUsers) + '\n';
        }

        this->CreateResultTypeMessage();
    }

    LobbyActionResult() { this->CreateResultTypeMessage(); }
private:
    std::string lobbyId;
    std::string lobbies;
    std::map<ResultTypeEnum, std::string> resultTypeMessages;
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