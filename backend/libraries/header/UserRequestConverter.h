#pragma once

#include <string>
#include <list>

#include <IRequestData.h>
#include <IRequestResult.h>

class UserRequestConverter
{
public:
    static IRequestData Convert(std::list<std::string> data);
};