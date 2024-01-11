#pragma once

#include <map>
#include <string>

#include <ResultType.h>

class IRequestResult
{
public:
    virtual std::string GetMessage() { return "unknown error"; }
};