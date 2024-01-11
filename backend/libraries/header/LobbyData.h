#pragma once

#include <string>

#include "IRequestData.h"

class LobbyData : public IRequestData
{
public:
    std::string userId;
};