#include "../header/Lobby.h"
#include "../header/GlobalSettings.h"

Lobby::Lobby()
{
    this->maxUsers = GlobalSettings::LobbyMaxUsers;
}

Lobby::LobbyResult Lobby::AddUser(User user)
{
    for (auto lobbyUser : this->lobbyUsers)
    {
        if (lobbyUser.id == user.id)
            return Lobby::LobbyResult::UserAlreadyInLobby;
    }

    this->lobbyUsers.push_back(user);
    return Lobby::LobbyResult::Success2;
}

int Lobby::GetUserCount()
{
    return this->lobbyUsers.size();
}