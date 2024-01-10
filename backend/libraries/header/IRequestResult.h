#pragma once

#include <map>
#include <string>

#include <ResultType.h>

class IRequestResult
{
public:
    enum ResultTypeEnum {};
    std::string GetMessage();
    ResultTypeEnum resultType;
    ResultType resultConclusion;
    virtual ~IRequestResult();
private:
    std::map<ResultTypeEnum, std::string> resultTypeMessages;
};