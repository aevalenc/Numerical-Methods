/*
 * Bisection method implementation for finding roots of a continuous function.
 *
 * Author: Alejandro Valencia
 * Update: August 14, 2025
 */

#include "root_finders/bisection_method/bisection_method.h"

namespace nm
{
namespace root_finders
{

double BisectionMethod(const std::function<double(double)>& function,
                       const double a,
                       const double b,
                       const double tolerance)
{
    const double mid = (a + b) / 2.0;
    if (std::abs(function(mid)) < tolerance)
    {
        return mid;
    }
    else if (function(a) * function(mid) < 0)
    {
        return BisectionMethod(function, a, mid, tolerance);
    }
    else
    {
        return BisectionMethod(function, mid, b, tolerance);
    }
}

}  // namespace root_finders
}  // namespace nm
