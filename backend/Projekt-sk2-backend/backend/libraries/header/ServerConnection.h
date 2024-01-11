#pragma once

#include <netinet/in.h>
#include <memory>

#include <User.h>

class ServerConnection
{
public:
    int clientId;
    sockaddr_in clientAddress;
    std::shared_ptr<User> user;
    bool connected;
};