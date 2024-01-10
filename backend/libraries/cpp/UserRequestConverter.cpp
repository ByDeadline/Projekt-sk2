#include <string>
#include <list>
#include <memory>

#include "../header/UserRequestConverter.h"
#include "../header/IRequestData.h"
#include "../header/IRequestResult.h"
#include "../header/UserData.h"

std::shared_ptr<IRequestData> UserRequestConverter::Convert(std::list<std::string> data)
{
    auto userData = std::make_shared<UserData>();
    userData->SetRequestType(RequestType::UserLogin);

    if (data.size() != 2)
    {
        userData->SetRequestType(RequestType::Unknown);
        return userData;
    }

    for (auto item : data)
    {
        if (item == "login")
            continue;
        
        userData->username = item;
    }

    return userData;
}