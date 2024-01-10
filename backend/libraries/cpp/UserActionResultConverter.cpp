#include "../header/UserActionResultConverter.h"

#include <memory>

std::string UserActionResultConverter::BuildUserLogin(std::shared_ptr<UserActionResult> userResult)
{
    return "success," + userResult->uniqueCode;
}

std::string UserActionResultConverter::BuildUsernameAlreadyExists(std::shared_ptr<UserActionResult> userResult)
{
    return "failed," + userResult->GetMessage();
}

std::string UserActionResultConverter::ConvertUserLogin(IRequestResult data)
{
    std::shared_ptr<UserActionResult> userResult(dynamic_cast<UserActionResult*>(&data));
    
    switch (userResult->resultType)
    {
        case UserActionResult::ResultTypeEnum::Success:
            return UserActionResultConverter::BuildUserLogin(userResult);
        case UserActionResult::ResultTypeEnum::UsernameAlreadyExists:
            return UserActionResultConverter::BuildUsernameAlreadyExists(userResult);
    }
    
    return "unknown error";
}