#pragma once
#include <IServerRequestHandler.h>

class TCPHandler : public IServerRequestHandler
{
private:
    void ListenForClinets();
    void HandleConnectionAsync(int fd, sockaddr_in clientAddress);

public:
    TCPHandler();
};