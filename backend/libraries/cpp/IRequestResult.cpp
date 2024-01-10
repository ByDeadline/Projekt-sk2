#include "../header/IRequestResult.h"

std::string IRequestResult::GetMessage()
{
    return this->resultTypeMessages[this->resultType];
}

IRequestResult::~IRequestResult()
{
    
}