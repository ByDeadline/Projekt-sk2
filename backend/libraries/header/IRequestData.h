#pragma once

#include <RequestType.h>

class IRequestData
{
private:
    RequestType requestType;

public:
    RequestType GetRequestType();
};