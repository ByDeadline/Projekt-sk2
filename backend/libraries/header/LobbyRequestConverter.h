#pragma once

#include <string>
#include <list>
#include <memory>

#include <IRequestData.h>
#include <IRequestResult.h>

/// @brief Converts text sent from the client to data aimed at Lobby
class LobbyRequestConverter
{
public:
    /// @brief Converts the text to a data object
    /// @param data A list of texts
    /// @return Data of the request
    static std::shared_ptr<IRequestData> Convert(std::list<std::string> data);
};