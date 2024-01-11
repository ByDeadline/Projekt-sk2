#pragma once

#include <string>
#include <list>
#include <memory>

#include <IRequestData.h>
#include <IRequestResult.h>

class LobbyRequestConverter
{
public:
    static std::shared_ptr<IRequestData> Convert(std::list<std::string> data);
};