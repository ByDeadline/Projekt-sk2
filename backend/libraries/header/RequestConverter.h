#pragma once

#include <string>
#include <list>
#include <memory>

#include <IRequestData.h>
#include <IRequestResult.h>

/// @brief A class that serializes or deserializes a request string to an object or vice versa
class RequestConverter
{
private:

    /// @brief A method that divides a string to a list of elements
    /// @param data A string with request
    /// @return List of string items
    static std::list<std::string> DivideData(std::string data);

public:
    static std::shared_ptr<IRequestData> Convert(std::string data);
    
    static std::string Convert(std::shared_ptr<IRequestResult> data);
};