#pragma once

class IServerRequestHandler
{
protected:
    bool listenOn = true;
    virtual void ListenForClinets() = 0;
    virtual void HandleConnectionAsync(int fd, sockaddr_in clientAddress) = 0;
};