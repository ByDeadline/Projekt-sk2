#include "../header/LobbyRequestConverter.h"
#include "../header/LobbyData.h"

std::shared_ptr<IRequestData> LobbyRequestConverter::Convert(std::list<std::string> data)
{
    auto lobbyData = std::make_shared<LobbyData>();

    bool requestFound = false;
    bool get2 = false;
    bool get3 = false;
    bool get4 = false;


    for (auto item : data)
    {
        if (item == "create_lobby" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::CreateLobby);
            get2 = true;
            continue;
        }

        if (item == "show_lobbies" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::ShowLobbies);
            get2 = true;
            continue;
        }

        if (item == "join_lobby" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::JoinLobby);
            get2 = true;
            get3 = true;
            continue;
        }

        if (item == "leave_lobby" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::LeaveLobby);
            get2 = true;
            get3 = true;
            continue;
        }

        if (item == "ready" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::SetReady);
            get2 = true;
            get3 = true;
            continue;
        }

        if (item == "progress" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::GiveProgress);
            get2 = true;
            get3 = true;
            get4 = true;
            continue;
        }

        if (item == "remove_lobby" && !requestFound)
        {
            requestFound = true;
            lobbyData->SetRequestType(RequestType::RemoveLobby);
            get2 = true;
            get3 = true;
            continue;
        }

        if (get2)
        {
            get2 = false;
            lobbyData->userId = item;
            if (!get3)
                return lobbyData;
            else
                continue;
        }

        if (get3)
        {
            get3 = false;
            lobbyData->lobbyId = item;
            if (!get4)
                return lobbyData;
            else 
                continue;
        }

        if (get4)
        {
            lobbyData->progress = item;
            return lobbyData;
        }

        if (!requestFound)
            break;
    }

    lobbyData->SetRequestType(RequestType::Unknown);
    return lobbyData;
}