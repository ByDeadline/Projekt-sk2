#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <poll.h>

#include <TCPHandler.h>
#include <GlobalSettings.h>
#include <Server.h>

TCPHandler::TCPHandler()
{
    this->ListenForClinets();
}

void TCPHandler::ListenForClinets()
{
    sockaddr_in serverAddress {};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(GlobalSettings::ServerPort);

    int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(fd, (sockaddr*)&serverAddress, sizeof(serverAddress));

    while (this->listenOn)
    {
        listen(fd, GlobalSettings::TCPSocketMaxRequests);

        sockaddr_in clientAddress {};
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientFd = accept(fd, (sockaddr*)&clientAddress, &clientAddressLength);
        std::thread(TCPHandler::HandleConnectionAsync, clientFd);
    }
}

void TCPHandler::HandleConnectionAsync(int fd, sockaddr_in clientAddress)
{
    auto clientConnection = Server::addServerConnection(clientAddress);

    pollfd clientPoll {};
    clientPoll.fd = fd;
    clientPoll.events = POLLIN;

    while (clientConnection->connected)
    {
        poll(&clientPoll, 1, GlobalSettings::TCPUserConnectionTimeout);
        if (clientPoll.revents & POLLIN)
        {
            char data[GlobalSettings::TCPMaxCharReadLength];
            int len = read(fd, data, sizeof(data) - 1);
            if (len > 0)
            {
                std::string text(data, len - 1);
                // tu odebrany tekst trzeba przekonwertować
            }
        }
        else
        {
            // klient nic nie robił przez 30s, sprawdźmy czy żyje.
        }
    }
}