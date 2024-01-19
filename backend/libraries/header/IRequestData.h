#pragma once

#include <RequestType.h>

/// @brief An interface for classes that hold data sent from the client
class IRequestData
{
private:
    /// @brief Type of request the client is making
    RequestType requestType;

public:
    /// @brief Id of the client that sent the request
    int clientId;

    /// @brief Virtual destructor
    virtual ~IRequestData();
    
    /// @brief Method that returns the type of request the client is making
    /// @return Type of request the client is making
    RequestType GetRequestType();

    /// @brief Method that sets the type of request the client is making
    /// @param requestType Type of request the client is making
    void SetRequestType(RequestType requestType);
};