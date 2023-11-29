#include <iostream>
#include <header/Rational.h>

int main()
{
    Rational rat(1,2);
    std::cout << rat.GetDouble() << std::endl;
    return 0;
}