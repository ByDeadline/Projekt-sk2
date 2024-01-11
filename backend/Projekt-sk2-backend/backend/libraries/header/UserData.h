#pragma once

#include <string>

#include <IRequestData.h>

class UserData : public IRequestData
{
public:
    std::string username;
};