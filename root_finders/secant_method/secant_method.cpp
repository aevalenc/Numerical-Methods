/*
 * Secant method implementation for finding roots of a continuous function.
 *
 * Author: Alejandro Valencia
 * Update: September 10th, 2025
 */

#include "root_finders/secant_method/secant_method.h"
#include <cstdint>
#include <cstdlib>

namespace nm
{
namespace root_finders
{

double SecantMethod(const std::function<double(double)>& function,
                    const double x0,
                    const double x1,
                    const double tolerance,
                    const std::int32_t max_iterations)
{
    double xkm1{x0};
    double xk{x1};
    double xkp1{0.0};
    for (std::int32_t k{1}; k < max_iterations; ++k)
    {
        xkp1 = xk - function(xk) * (xk - xkm1) / (function(xk) - function(xkm1));
        if (std::abs(xkp1 - xk) < tolerance)
        {
            break;
        }
    }
    return xkp1;
}

}  // namespace root_finders
}  // namespace nm
