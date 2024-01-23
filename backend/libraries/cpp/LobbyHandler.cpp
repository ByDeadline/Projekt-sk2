#include <thread>

#include "../header/LobbyHandler.h"
#include "../header/LobbyData.h"
#include "../header/UserHandler.h"
#include "../header/LobbyActionResult.h"
#include "../header/Log.h"
#include "../header/Server.h"
#include "../header/Game.h"
#include "../header/GameActionResult.h"

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

Lobby::LobbyResult LobbyHandler::GetReady(std::string userId, std::string lobbyId)
{
    auto lobby = LobbyHandler::GetLobbyById(lobbyId);
    if (lobby != nullptr && lobby->lobbyId == lobbyId)
            return lobby->SetUserReady(userId);

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

std::shared_ptr<Lobby> LobbyHandler::CheckUserInAnyLobby(std::string userId)
{
    for (auto lobby : LobbyHandler::lobbies)
    {
        if (lobby->CheckUserInLobby(userId))
            return lobby;
    }

    return nullptr;
}

void LobbyHandler::RemoveUserFromLobby(std::string userId)
{
    auto lobby = LobbyHandler::CheckUserInAnyLobby(userId);
    if (lobby != nullptr)
    {
        lobby->RemoveUser(userId, true);
    }
}

void LobbyHandler::RemoveLobby(std::string lobbyId)
{
    LobbyHandler::lobbies.remove_if([=](std::shared_ptr<Lobby> lobby) { return lobby->lobbyId == lobbyId; });
}

std::shared_ptr<IRequestResult> LobbyHandler::HandleJoinLobby(std::shared_ptr<IRequestData> requestData)
{
    auto lobbyData = std::make_shared<LobbyData>(*dynamic_cast<LobbyData*>(requestData.get()));
    auto user = UserHandler::GetUserByUserId(lobbyData->userId);

    auto lobbyActionResult = std::make_shared<LobbyActionResult>();

    if (user != nullptr)
    {
        if (LobbyHandler::CheckUserInAnyLobby(lobbyData->userId) == nullptr)
        {
            auto lobby = LobbyHandler::GetLobbyById(lobbyData->lobbyId);
            auto joinResult = LobbyHandler::JoinLobby(lobbyData->userId, lobbyData->lobbyId);
            switch (joinResult)
            {
                case Lobby::LobbyResult::Success2:
                    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::Success1;
                    lobbyActionResult->setLobbyId(lobbyData->lobbyId);
                    Log::Write(std::to_string(lobbyData->clientId) + ": Successfully created a lobby with id: " + lobbyData->lobbyId);
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

        lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::AlreadyInLobby;
        Log::Write(std::to_string(lobbyData->clientId) + ": This user is already in a lobby.");

        return lobbyActionResult;
    }

    Log::Write(std::to_string(lobbyData->clientId) + ": User not logged in.");
    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::NotLoggedIn;
    return lobbyActionResult;
}

std::shared_ptr<IRequestResult> LobbyHandler::HandleLeaveLobby(std::shared_ptr<IRequestData> requestData)
{
    auto lobbyData = std::make_shared<LobbyData>(*dynamic_cast<LobbyData*>(requestData.get()));
    auto user = UserHandler::GetUserByUserId(lobbyData->userId);

    auto lobbyActionResult = std::make_shared<LobbyActionResult>();

    if (user != nullptr)
    {
        auto lobby = LobbyHandler::GetLobbyById(lobbyData->lobbyId);
        if (lobby == nullptr)
        {
            lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::LobbyNotFound;
            Log::Write(std::to_string(lobbyData->clientId) + ": This user tried to leave a non existent lobby.");
            return lobbyActionResult;
        }

        auto removeResult = lobby->RemoveUser(lobbyData->userId);
        switch (removeResult)
        {
            case Lobby::LobbyResult::UserNotInLobby:
                Log::Write(std::to_string(lobbyData->clientId) + ": The user is not in this lobby");
                lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::NotInLobby;
                return lobbyActionResult;
        }

        Log::Write(std::to_string(lobbyData->clientId) + ": Removed user " + lobbyData->userId + " from lobby " + lobbyData->lobbyId);
        lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::Success1;
        lobbyActionResult->setLobbyId(lobbyData->lobbyId);
        return lobbyActionResult;
    }

    Log::Write(std::to_string(lobbyData->clientId) + ": User not logged in.");
    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::NotLoggedIn;
    return lobbyActionResult;
}

std::shared_ptr<IRequestResult> LobbyHandler::HandleCreateLobby(std::shared_ptr<IRequestData> requestData)
{
    auto lobbyData = std::make_shared<LobbyData>(*dynamic_cast<LobbyData*>(requestData.get()));
    auto user = UserHandler::GetUserByUserId(lobbyData->userId);

    auto lobbyActionResult = std::make_shared<LobbyActionResult>();

    if (user != nullptr)
    {
        if (LobbyHandler::CheckUserInAnyLobby(lobbyData->userId) == nullptr)
        {
            auto lobbyId = LobbyHandler::CreateLobby();
            lobbyData->lobbyId = lobbyId;
            return LobbyHandler::HandleJoinLobby(lobbyData);
        }

        lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::AlreadyInLobby;
        Log::Write(std::to_string(lobbyData->clientId) + ": This user is already in a lobby.");
        return lobbyActionResult;
    }

    Log::Write(std::to_string(lobbyData->clientId) + ": User not logged in.");
    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::NotLoggedIn;
    return lobbyActionResult;
}

void LobbyHandler::AsyncStartGame(std::string lobbyId)
{
    auto lobby = LobbyHandler::GetLobbyById(lobbyId);
    lobby->StartGame();
    auto gameActionResult = std::make_shared<GameActionResult>();
    gameActionResult->setText(lobby->game->GetText(), lobby->game->GetWordCount(), lobby->game->players);
    gameActionResult->resultType = GameActionResult::ResultTypeEnum::SendText;

    Log::Write("Number of words to be written: " + lobby->game->GetWordCount());
    Server::Send(lobby->lobbyUsers, gameActionResult);
}

std::shared_ptr<IRequestResult> LobbyHandler::HandleProgressUpdate(std::shared_ptr<IRequestData> requestData)
{
    auto lobbyData = std::make_shared<LobbyData>(*dynamic_cast<LobbyData*>(requestData.get()));
    auto gameActionResult = std::make_shared<GameActionResult>();

    auto lobby = LobbyHandler::GetLobbyById(lobbyData->lobbyId);
    if (lobby->gameInProgress)
    {
        try
        {
            int progress = std::stoi(lobbyData->progress);
            lobby->game->SetPlayerProgress(lobbyData->userId, progress);

            gameActionResult->setStatus(lobby->game->players);
            if (lobby->game->IsFinished())
            {
                gameActionResult->resultType = GameActionResult::ResultTypeEnum::FinishGame;
                Log::Write("Game in lobby " + lobbyData->lobbyId + " finished");
                Server::Send(lobby->game->players, gameActionResult);
                LobbyHandler::RemoveLobby(lobby->lobbyId);
            }
            else
            {
                gameActionResult->resultType = GameActionResult::ResultTypeEnum::SendStatus;
                Server::Send(lobby->game->players, gameActionResult);
            }
        }
        catch (...)
        {
        }

    }

    return nullptr;
}

void LobbyHandler::CheckAllReady(std::string lobbyId)
{
    auto lobby = LobbyHandler::GetLobbyById(lobbyId);
    if (lobby->GetUserCount() > 1 && lobby->CheckAllUsersReady())
    {
        Log::Write("Game started in lobby " + lobbyId);
        LobbyHandler::AsyncStartGame(lobbyId);
    }
}

std::shared_ptr<IRequestResult> LobbyHandler::HandleReady(std::shared_ptr<IRequestData> requestData)
{
    auto lobbyData = std::make_shared<LobbyData>(*dynamic_cast<LobbyData*>(requestData.get()));
    auto user = UserHandler::GetUserByUserId(lobbyData->userId);

    auto lobbyActionResult = std::make_shared<LobbyActionResult>();

    if (user != nullptr)
    {
        if (LobbyHandler::GetLobbyById(lobbyData->lobbyId)->CheckUserInLobby(lobbyData->userId))
        {
            auto getReadyResult = LobbyHandler::GetReady(lobbyData->userId, lobbyData->lobbyId);
            switch (getReadyResult)
            {
                case Lobby::LobbyResult::LobbyDoesNotExist:
                    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::LobbyNotFound;
                    Log::Write(std::to_string(lobbyData->clientId) + ": This user tried to be ready in a lobby that does not exist.");
                    break;
                case Lobby::LobbyResult::GameInProgress:
                    lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::GameInProgress;
                    Log::Write(std::to_string(lobbyData->clientId) + ": This user tried to join to a lobby that is already in game.");
                    break;
            }
        }
        else
        {
            lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::NotInLobby;
            Log::Write(std::to_string(lobbyData->clientId) + ": The user is not in this lobby");
            return lobbyActionResult;
        }

        lobbyActionResult->resultType = LobbyActionResult::ResultTypeEnum::Success1;
        lobbyActionResult->setLobbyId(lobbyData->lobbyId);
        Log::Write(std::to_string(lobbyData->clientId) + ": Successfully set the player ready");
        LobbyHandler::CheckAllReady(lobbyData->lobbyId);
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