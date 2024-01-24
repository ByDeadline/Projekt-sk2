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

    bool requestFound = false;
    bool get2 = false;
    bool get3 = false;

    for (auto item : data)
    {
        if (item == "login" && !requestFound)
        {
            requestFound = true;
            userData->SetRequestType(RequestType::UserLogin);
            continue;
        }

        if (item == "admin" && !requestFound)
        {
            requestFound = true;
            userData->SetRequestType(RequestType::UserLogin);
            userData->admin = true;
            continue;
        }
        
        if (item == "remove_user" && !requestFound)
        {
            requestFound = true;
            get2 = true;
            get3 = true;
            userData->SetRequestType(RequestType::RemoveUser);
            continue;
        }

        if (item == "show_users" && !requestFound)
        {
            requestFound = true;
            get2 = true;
            userData->SetRequestType(RequestType::ShowUsers);
            continue;
        }

        if (item == "logout" && !requestFound)
        {
            requestFound = true;
            get2 = true;
            userData->SetRequestType(RequestType::UserLogout);
            continue;
        }

        if (item == "alive" && !requestFound)
        {
            requestFound = true;
            userData->SetRequestType(RequestType::Alive);
            continue;
        }

        if (get2)
        {
            userData->userId = item;
            get2 = false;
            if (!get3)
                return userData;
            continue;
        }

        if (get3)
        {
            userData->userToDelete = item;
            return userData;
            
        }

        if (!get2)
        {
            userData->username = item;
            return userData;
        }
            
    }

    userData->SetRequestType(RequestType::Unknown);
    return userData;
}