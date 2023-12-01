#include <Rational.h>

Rational::Rational(int p, int q)
{
    this->p = p;
    this->q = q;
}

double Rational::GetDouble()
{
    return (double)this->p / (double)this->q;
}