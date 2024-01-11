#pragma once

#include <string>
#include <list>

#include "User.h"

class Lobby
{
public:
    enum LobbyResult
    {
        Success2,
        UserAlreadyInLobby,
        LobbyFull,
        LobbyDoesNotExist
    };

    int maxUsers;
    std::string lobbyId;
    std::list<User> lobbyUsers;
    
    Lobby();
    LobbyResult AddUser(User user);
    int GetUserCount();
};