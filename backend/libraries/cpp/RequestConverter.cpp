#include <string>
#include <list>

#include "../header/RequestConverter.h"
#include "../header/IRequestData.h"
#include "../header/IRequestResult.h"
#include "../header/UserRequestConverter.h"
#include "../header/RequestType.h"
#include "../header/UserActionResultConverter.h"

std::list<std::string> RequestConverter::DivideData(std::string data)
{
    std::list<std::string> items;

    int separatorPosition = data.find(",");
    while (separatorPosition != std::string::npos)
    {
        items.push_back(data.substr(0, separatorPosition));
        data = data.substr(separatorPosition + 1);
        separatorPosition = data.find(",");
    }

    return items;
}

IRequestData RequestConverter::Convert(std::string data)
{
    std::list<std::string> items = RequestConverter::DivideData(data);
    
    if (items.size() != 0)
    {
        if (items.front() == "login")
            return UserRequestConverter::Convert(items);
    }

    IRequestData unknownData;
    unknownData.SetRequestType(RequestType::Unknown);
    return unknownData;
}

std::string RequestConverter::Convert(IRequestResult data)
{
    switch (data.resultConclusion)
    {
        case RequestType::UserLogin:
            return UserActionResultConverter::ConvertUserLogin(data);
    }

    return "unknown error";
}