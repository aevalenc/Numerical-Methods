/*
 * Trapezoidal Numerical Integration Implementations
 *
 * Author: Alejandro Valencia
 * Update: August 14, 2025
 *
 */

#include "calculus/integration/trapezoidal_method/trapezoidal_method.h"

namespace nm
{
namespace calculus
{

double TrapezoidalIntegration(const std::function<double(double)>& function,
                              const double a,
                              const double b,
                              const std::int32_t n)
{
    const auto subinterval_length = (b - a) / n;

    double sum{function(a)};
    for (std::int32_t i{1}; i < n; ++i)
    {
        sum += 2 * function(a + i * subinterval_length);
    }
    sum += function(b);

    return (subinterval_length / 2) * sum;
}

}  // namespace calculus
}  // namespace nm
