#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <poll.h>
#include <memory>

#include "../header/TCPHandler.h"
#include "../header/GlobalSettings.h"
#include "../header/Server.h"
#include "../header/RequestConverter.h"
#include "../header/IRequestData.h"
#include "../header/Log.h"

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

    Log::Write("TCP listen started.");
    while (this->listenOn)
    {
        listen(fd, GlobalSettings::TCPSocketMaxRequests);

        sockaddr_in clientAddress {};
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientFd = accept(fd, (sockaddr*)&clientAddress, &clientAddressLength);
        std::thread* th = new std::thread(TCPHandler::HandleConnectionAsync, clientFd, clientAddress);
    }
}

void TCPHandler::HandleConnectionAsync(int fd, sockaddr_in clientAddress)
{
    char addressChar[GlobalSettings::MaxCharAddressLength];
    inet_ntop(AF_INET, &(clientAddress.sin_addr), addressChar, GlobalSettings::MaxCharAddressLength);
    std::string ipAddress(addressChar);

    auto clientConnection = Server::AddServerConnection(clientAddress);
    Log::Write("New user connection from " + ipAddress + ". Assgined id: " + std::to_string(clientConnection->clientId));

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
                std::string recivedText(data, len - 1);

                Log::Write(std::to_string(clientConnection->clientId) + ": sent request to TCP handler. Contents: '" + recivedText + "'");

                auto requestData = RequestConverter::Convert(recivedText);
                requestData->clientId = clientConnection->clientId;
                auto requestResult = Server::ReciveRequest(requestData);
                std::string textToSend = RequestConverter::Convert(requestResult);
                write(fd, textToSend.c_str(), textToSend.size());

                Log::Write(std::to_string(clientConnection->clientId) + ": TCP handler answered with contents: '" + textToSend + "'");
            }
        }
        else
        {
            // klient nic nie robił przez 30s, sprawdźmy czy żyje.
        }
    }
}