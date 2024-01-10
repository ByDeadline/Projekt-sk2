#pragma once

#include <string>
#include <memory>

#include <IRequestResult.h>
#include <UserActionResult.h>

class UserActionResultConverter
{
public:
    static std::string ConvertUserLogin(std::shared_ptr<IRequestResult> data);
    static std::string BuildUserLogin(std::shared_ptr<UserActionResult> data);
    static std::string BuildError(std::shared_ptr<UserActionResult> userResult);
};