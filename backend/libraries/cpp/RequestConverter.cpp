#include <string>
#include <list>

#include <RequestConverter.h>
#include <IRequestData.h>
#include <IRequestResult.h>

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
    
}