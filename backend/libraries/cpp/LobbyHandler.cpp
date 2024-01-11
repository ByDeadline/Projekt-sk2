#include "../header/LobbyHandler.h"
#include "../header/LobbyData.h"
#include "../header/UserHandler.h"
#include "../header/LobbyActionResult.h"
#include "../header/Log.h"

std::list<std::shared_ptr<Lobby>> LobbyHandler::lobbies;
int LobbyHandler::lobbyIdCounter = 0;

std::string LobbyHandler::CreateLobby()
{
    auto lobby = std::make_shared<Lobby>();
    lobby->lobbyId = "$" + std::to_string(LobbyHandler::lobbyIdCounter++);
    LobbyHandler::lobbies.push_back(lobby);

    return lobby->lobbyId;
}

Lobby::LobbyResult LobbyHandler::JoinLobby(std::string userId, std::string lobbyId)
{
    for (auto lobby : LobbyHandler::lobbies)
    {
        if (lobby->lobbyId == lobbyId)
        {
            auto user = UserHandler::GetUserByUserId(userId);
            return lobby->AddUser(*user);
        }
    }

    return Lobby::LobbyResult::LobbyDoesNotExist;
}

std::shared_ptr<Lobby> LobbyHandler::GetLobbyById(std::string lobbyId)
{
    for (auto lobby : LobbyHandler::lobbies)
    {
        if (lobby->lobbyId == lobbyId)
            return lobby;
    }

    return nullptr;
}

std::shared_ptr<IRequestResult> LobbyHandler::HandleCreateLobby(std::shared_ptr<IRequestData> requestData)
{
    auto lobbyData = std::make_shared<LobbyData>(*dynamic_cast<LobbyData*>(requestData.get()));
    auto user = UserHandler::GetUserByUserId(lobbyData->userId);

    auto lobbyActionResult = std::make_shared<LobbyActionResult>();

    if (user != nullptr)
    {
        auto lobbyId = LobbyHandler::CreateLobby();
        auto lobby = LobbyHandler::GetLobbyById(lobbyId);

        auto createResult = LobbyHandler::JoinLobby(lobbyData->userId, lobbyId);

        switch (createResult)
        {
            case Lobby::LobbyResult::Success2:
                lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::Success1;
                lobbyActionResult->setLobbyId(lobbyId);
                Log::Write(std::to_string(lobbyData->clientId) + ": Successfully created a lobby with id: " + lobbyId);
                break;
            case Lobby::LobbyResult::UserAlreadyInLobby:
                lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::AlreadyInLobby;
                Log::Write(std::to_string(lobbyData->clientId) + ": This user is already in a lobby.");
                break;
            case Lobby::LobbyResult::LobbyFull:
                lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::LobbyFull;
                Log::Write(std::to_string(lobbyData->clientId) + ": This user can't join because the lobby is full. "  + std::to_string(lobby->GetUserCount()) + "/" + std::to_string(lobby->maxUsers));
                break;
            case Lobby::LobbyResult::LobbyDoesNotExist:
                lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::LobbyNotFound;
                Log::Write(std::to_string(lobbyData->clientId) + ": This user tried to join a non existent lobby.");
                break;
        }

        return lobbyActionResult;
    }

    Log::Write(std::to_string(lobbyData->clientId) + ": User not logged in.");
    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::NotLoggedIn;
    return lobbyActionResult;
}

std::shared_ptr<IRequestResult> LobbyHandler::HandleShowLobbies(std::shared_ptr<IRequestData> requestData)
{
    auto lobbyData = std::make_shared<LobbyData>(*dynamic_cast<LobbyData*>(requestData.get()));
    auto user = UserHandler::GetUserByUserId(lobbyData->userId);

    auto lobbyActionResult = std::make_shared<LobbyActionResult>();

    if (user != nullptr)
    {
        lobbyActionResult->setLobbies(LobbyHandler::lobbies);
        lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::SuccessLobbies;
        Log::Write(std::to_string(lobbyData->clientId) + ": Successfully read the lobbies.");
        return lobbyActionResult;
    }

    Log::Write(std::to_string(lobbyData->clientId) + ": User not logged in.");
    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::NotLoggedIn;
    return lobbyActionResult;
}