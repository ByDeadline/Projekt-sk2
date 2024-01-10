#include "../header/UserActionResultConverter.h"

#include <memory>

std::string UserActionResultConverter::BuildUserLogin(std::shared_ptr<UserActionResult> userResult)
{
    return "success," + userResult->uniqueCode;
}

std::string UserActionResultConverter::BuildError(std::shared_ptr<UserActionResult> userResult)
{
    return "failed," + userResult->GetMessage();
}

std::string UserActionResultConverter::ConvertUserLogin(std::shared_ptr<IRequestResult> data)
{
    auto userResult = std::make_shared<UserActionResult>(*dynamic_cast<UserActionResult*>(data.get()));
    
    switch (userResult->resultType)
    {
        case UserActionResult::ResultTypeEnum::Success:
            return UserActionResultConverter::BuildUserLogin(userResult);
        default:
            return UserActionResultConverter::BuildError(userResult);
    }
    
    return "unknown error";
}