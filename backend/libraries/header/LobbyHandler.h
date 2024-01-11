#pragma once

#include <memory>
#include <list>
#include <string>

#include <IRequestData.h>
#include <User.h>
#include "../header/LobbyActionResult.h"

class LobbyHandler
{
public:
    IRequestResult HandleCreateLobby(std::shared_ptr<IRequestData> requestData);
};