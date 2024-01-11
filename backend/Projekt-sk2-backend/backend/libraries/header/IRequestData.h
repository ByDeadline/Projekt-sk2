#pragma once

#include <RequestType.h>

class IRequestData
{
private:
    RequestType requestType;

public:
    int clientId;

    virtual ~IRequestData();
    RequestType GetRequestType();
    void SetRequestType(RequestType requestType);
};