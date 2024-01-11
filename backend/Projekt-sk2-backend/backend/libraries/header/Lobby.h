#pragma once

#include <string>
#include <list>

#include "User.h"

class Lobby
{
public:
    std::string lobbyId;
    std::list<User> lobbyUsers;
};