#include <memory>
#include <map>

#include "../header/Lobby.h"
#include "../header/GlobalSettings.h"
#include "../header/LobbyActionResult.h"
#include "../header/Server.h"

Lobby::Lobby()
{
    this->maxUsers = GlobalSettings::LobbyMaxUsers;
}

void Lobby::SendLobbyStatus()
{
    auto lobbyActionResult = std::make_shared<LobbyActionResult>();
    std::map<std::string, bool> usersInfo;

    for (auto user : this->lobbyUsers)
        usersInfo.insert({user.username, user.isReady});
    
    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::LobbyStatus;
    lobbyActionResult->setLobbyStatus(usersInfo);
    Server::Send(this->lobbyUsers, lobbyActionResult);
}

int Lobby::GetUserCount()
{
    return this->lobbyUsers.size();
}

Player Lobby::CreatePlayer(User user)
{
    Player player;
    player.id = user.id;
    player.username = user.username;

    return player;
}

Lobby::LobbyResult Lobby::AddUser(User user)
{
    if (this->gameInProgress)
        return Lobby::LobbyResult::GameInProgress;

    if (this->GetUserCount() >= this->maxUsers)
        return Lobby::LobbyResult::LobbyFull;

    for (auto lobbyUser : this->lobbyUsers)
    {
        if (lobbyUser.id == user.id)
            return Lobby::LobbyResult::UserAlreadyInLobby;
    }

    this->lobbyUsers.push_back(CreatePlayer(user));
    this->SendLobbyStatus();
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

Lobby::LobbyResult Lobby::RemoveUser(std::string userId, bool forceRemove)
{
    if (this->gameInProgress && !forceRemove)
        return Lobby::LobbyResult::GameInProgress;

    if (this->CheckUserInLobby(userId))
    {
        this->lobbyUsers.remove_if([=](User user) { return user.id == userId; });
        this->SendLobbyStatus();

        return Lobby::LobbyResult::Success2;
    }

    return Lobby::LobbyResult::UserNotInLobby;
}

Lobby::LobbyResult Lobby::SetUserReady(std::string userId)
{
    if (this->gameInProgress)
        return Lobby::LobbyResult::GameInProgress;

    for (Player &user : this->lobbyUsers)
    {
        if (user.id == userId)
        {
            user.isReady = true;
            this->SendLobbyStatus();

            return Lobby::LobbyResult::Success2;
        }
    }

    return Lobby::LobbyResult::UserNotInLobby;
}

void Lobby::StartGame()
{
    this->gameInProgress = true;
    this->game = std::make_shared<Game>(this->lobbyUsers);
}

bool Lobby::CheckAllUsersReady()
{
    for (auto user : this->lobbyUsers)
    {
        if (!user.isReady)
            return false;
    }

    return true;
}