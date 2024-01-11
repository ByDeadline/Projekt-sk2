#include "../header/LobbyRequestConverter.h"
#include "../header/LobbyData.h"

std::shared_ptr<IRequestData> LobbyRequestConverter::Convert(std::list<std::string> data)
{
    auto lobbyData = std::make_shared<LobbyData>();

    if (data.size() != 2)
    {
        lobbyData->SetRequestType(RequestType::Unknown);
    }

    bool createLobby = false;
    bool showLobbies = false;

    for (auto item : data)
    {
        if (item == "create_lobby")
        {
            createLobby = true;
            continue;
        }

        if (item == "show_lobbies")
        {
            showLobbies = true;
            continue;
        }

        if (createLobby)
        {
            lobbyData->SetRequestType(RequestType::CreateLobby);
            lobbyData->userId = item;
            return lobbyData;
        }

        if (showLobbies)
        {
            lobbyData->SetRequestType(RequestType::ShowLobbies);
            lobbyData->userId = item;
            return lobbyData;
        }
    }

    lobbyData->SetRequestType(RequestType::Unknown);
    return lobbyData;
}