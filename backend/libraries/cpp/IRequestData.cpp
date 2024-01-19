#include "../header/IRequestData.h"

RequestType IRequestData::GetRequestType()
{
    return IRequestData::requestType;
}

void IRequestData::SetRequestType(RequestType requestType)
{
    this->requestType = requestType;
}

IRequestData::~IRequestData()
{
    
}