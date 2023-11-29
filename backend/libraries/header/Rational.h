#pragma once

/// @brief Numerical type that stores a number as p/q
class Rational
{
private:
    /// @brief Represents a numerator
    int p;

    /// @brief Represents a denominator
    int q;

public:
    /// @brief Creates a Rational number
    /// @param p The numerator
    /// @param q The denominator
    Rational(int p, int q);

    /// @brief Converts the Rational object to a double
    /// @return A number converted to double
    double GetDouble();
};