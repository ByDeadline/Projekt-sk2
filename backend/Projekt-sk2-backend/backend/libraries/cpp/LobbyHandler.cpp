#include "../header/LobbyHandler.h"
#include "../header/LobbyData.h"

IRequestResult LobbyHandler::HandleCreateLobby(std::shared_ptr<IRequestData> requestData)
{
    auto lobbyData = std::make_shared<LobbyData>(*dynamic_cast<LobbyData*>(requestData.get()));
}