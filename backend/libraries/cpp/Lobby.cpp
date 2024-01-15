#include "../header/Lobby.h"
#include "../header/GlobalSettings.h"

Lobby::Lobby()
{
    this->maxUsers = GlobalSettings::LobbyMaxUsers;
}

int Lobby::GetUserCount()
{
    return this->lobbyUsers.size();
}

Lobby::LobbyResult Lobby::AddUser(User user)
{
    if (this->GetUserCount() >= this->maxUsers)
        return Lobby::LobbyResult::LobbyFull;

    for (auto lobbyUser : this->lobbyUsers)
    {
        if (lobbyUser.id == user.id)
            return Lobby::LobbyResult::UserAlreadyInLobby;
    }

    this->lobbyUsers.push_back(user);
    return Lobby::LobbyResult::Success2;
}

bool Lobby::CheckUserInLobby(std::string userId)
{
    for (auto user : this->lobbyUsers)
    {
        if (user.id == userId)
            return true;
    }

    return false;
}

Lobby::LobbyResult Lobby::RemoveUser(std::string userId)
{
    if (this->CheckUserInLobby(userId))
    {
        this->lobbyUsers.remove_if([=](User user) { return user.id == userId; });
        
        return Lobby::LobbyResult::Success2;
    }

    return Lobby::LobbyResult::UserNotInLobby;
}