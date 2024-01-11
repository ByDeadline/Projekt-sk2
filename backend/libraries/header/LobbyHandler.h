#pragma once

#include <memory>
#include <list>
#include <string>

#include <IRequestData.h>
#include <User.h>
#include "../header/LobbyActionResult.h"
#include "Lobby.h"

class LobbyHandler
{
private:
    static std::list<std::shared_ptr<Lobby>> lobbies;
    static int lobbyIdCounter;

public:
    static std::string CreateLobby();
    static Lobby::LobbyResult JoinLobby(std::string userId, std::string lobbyId);
    static std::shared_ptr<Lobby> GetLobbyById(std::string lobbyId);
    static std::shared_ptr<IRequestResult> HandleCreateLobby(std::shared_ptr<IRequestData> requestData);
    static std::shared_ptr<IRequestResult> HandleShowLobbies(std::shared_ptr<IRequestData> requestData);
};