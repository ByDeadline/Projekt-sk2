#pragma once

class GlobalSettings
{
public:
    static const int ServerPort = 1234;
    static const int TCPSocketMaxRequests = 100;
    static const int TCPMaxCharReadLength = 256;
    static const int TCPUserConnectionTimeout = 30000;
};