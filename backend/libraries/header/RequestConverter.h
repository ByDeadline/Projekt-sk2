#pragma once

#include <string>
#include <list>

#include <IRequestData.h>
#include <IRequestResult.h>

class RequestConverter
{
private:
    static std::list<std::string> RequestConverter::DivideData(std::string data);

public:
    static IRequestData Convert(std::string data);
    static std::string Convert(IRequestResult data);
};