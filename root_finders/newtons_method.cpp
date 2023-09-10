/*
 * Author : Alejandro Valencia
 * Project: Newton's Method
 * Update : September 10, 2023
 */

#include "root_finders/newtons_method.h"
#include <cmath>
#include <iostream>

namespace nm
{

namespace polysolver
{

namespace
{
bool IsNear(const double value_1, const double value_2, const double tolerance = std::numeric_limits<double>::epsilon())
{
    return std::islessequal((std::fabs(value_1 - value_2)), tolerance);
}
}  // namespace

double NewtonsMethod(double& x_0,
                     const std::function<double(double)>& function,
                     const std::function<double(double)>& derivative,
                     const double tolerance,
                     const std::int32_t max_iterations)
{
    double x_n{};

    for (std::int32_t i{0}; i < max_iterations; ++i)
    {
        if (IsNear(derivative(x_0), 0.0, tolerance))
        {
            std::cout << "Error: derivative evaluated at x is zero!"
                      << "\n";
        }

        x_n = x_0 - (function(x_0) / derivative(x_0));

        if (std::abs(x_n - x_0) < tolerance)
        {
            break;
        }
        x_0 = x_n;
    }

    return x_n;
}

}  // namespace polysolver

}  // namespace nm
