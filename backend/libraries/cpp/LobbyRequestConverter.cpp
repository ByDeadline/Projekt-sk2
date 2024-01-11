#include "../header/LobbyRequestConverter.h"
#include "../header/LobbyData.h"

std::shared_ptr<IRequestData> LobbyRequestConverter::Convert(std::list<std::string> data)
{
    auto lobbyData = std::make_shared<LobbyData>();

    if (data.size() != 2)
    {
        lobbyData->SetRequestType(RequestType::Unknown);
    }

    bool requestFound = false;

    bool createLobby = false;
    bool showLobbies = false;

    bool joinLobby = false;
    bool getLobbyId = false;

    for (auto item : data)
    {
        if (item == "create_lobby" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::CreateLobby);
            createLobby = true;
            continue;
        }

        if (item == "show_lobbies" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::ShowLobbies);
            showLobbies = true;
            continue;
        }

        if (item == "join_lobby" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::JoinLobby);
            joinLobby = true;
            continue;
        }

        if (createLobby)
        {
            
            lobbyData->userId = item;
            return lobbyData;
        }

        if (showLobbies)
        {
            
            lobbyData->userId = item;
            return lobbyData;
        }

        if (joinLobby)
        {
            lobbyData->userId = item;
            getLobbyId = true;
            joinLobby = false;
            continue;
        }
        if (getLobbyId)
        {
            lobbyData->lobbyId = item;
            return lobbyData;
        }

        if (!requestFound)
            break;
    }

    lobbyData->SetRequestType(RequestType::Unknown);
    return lobbyData;
}