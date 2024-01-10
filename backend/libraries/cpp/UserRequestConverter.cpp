#include <string>
#include <list>

#include "../header/UserRequestConverter.h"
#include "../header/IRequestData.h"
#include "../header/IRequestResult.h"
#include "../header/UserData.h"

IRequestData UserRequestConverter::Convert(std::list<std::string> data)
{
    UserData userData;
    userData.SetRequestType(RequestType::UserLogin);

    if (data.size() > 2)
    {
        userData.SetRequestType(RequestType::Unknown);
        return userData;
    }

    for (auto item : data)
    {
        if (item == "login")
            continue;
        
        userData.username = item;
    }

    return userData;
}