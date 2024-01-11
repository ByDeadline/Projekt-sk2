#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <thread>

#include <TCPHandler.h>
#include "libraries/header/Config.h"

int main()
{
    Config::setUpLog();
    Config::updateSettings();

    std::thread tcpThread([]() {
        TCPHandler tcpHandler;
    });

    tcpThread.join();

    return 0;
}
