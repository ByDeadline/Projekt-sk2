#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

#include <Rational.h>

int main()
{
    sockaddr_in serverAddress {};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(1234);

    int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(fd, (sockaddr*)&serverAddress, sizeof(serverAddress));

    listen(fd, 1);

    sockaddr_in clientAddress {};
    socklen_t clientAddressLength = sizeof(clientAddress);
    int client_fd = accept(fd, (sockaddr*)&clientAddress, &clientAddressLength);
    std::cout << "Accepted connection" << std::endl;

    while (true)
    {
        char data[256];
        int len = read(client_fd, data, sizeof(data) - 1);

        if (len > 0)
        {
            std::string text(data, len - 1);
            if (text == "exit")
                break;
            std::cout << text << std::endl;
        }
    }

    close(client_fd);
    close(fd);
    return 0;
}