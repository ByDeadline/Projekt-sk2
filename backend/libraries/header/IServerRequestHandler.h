#pragma once

/// @brief An interface which has methods that use sockets to communicate directly with clients
class IServerRequestHandler
{
protected:
    /// @brief A flag that decides whether to accept new connections
    bool listenOn = true;
    
    /// @brief A method that listens for new clients
    virtual void ListenForClinets() = 0;
};