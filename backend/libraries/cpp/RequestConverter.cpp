#include <string>
#include <list>
#include <memory>

#include "../header/RequestConverter.h"
#include "../header/IRequestData.h"
#include "../header/IRequestResult.h"
#include "../header/UserRequestConverter.h"
#include "../header/RequestType.h"
#include "../header/LobbyRequestConverter.h"

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

    separatorPosition = data.find(";");
    if (separatorPosition != std::string::npos)
    {
        items.push_back(data.substr(0, separatorPosition));
    }
    else
    {
        items.push_back(data);
    }

    return items;
}

std::shared_ptr<IRequestData> RequestConverter::Convert(std::string data)
{
    std::list<std::string> items = RequestConverter::DivideData(data);
    
    if (items.size() != 0)
    {
        if (items.front() == "login" || items.front() == "logout" || items.front() == "alive")
            return UserRequestConverter::Convert(items);
        else if (items.front() == "create_lobby" || items.front() == "show_lobbies" || items.front() == "join_lobby" || items.front() == "leave_lobby" || items.front() == "ready"
                || items.front() == "progress")
            return LobbyRequestConverter::Convert(items);
    }

    auto unknownData = std::make_shared<IRequestData>();
    unknownData->SetRequestType(RequestType::Unknown);
    return unknownData;
}

std::string RequestConverter::Convert(std::shared_ptr<IRequestResult> data)
{
    return data->GetMessage();
}