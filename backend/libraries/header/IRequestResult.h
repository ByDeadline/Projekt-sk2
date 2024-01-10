#pragma once

#include <map>
#include <string>

#include <ResultType.h>

class IRequestResult
{
public:
    enum ResultTypeEnum {};
    virtual std::string GetMessage() { return ""; }
    ResultTypeEnum resultType;
    ResultType resultConclusion;
};