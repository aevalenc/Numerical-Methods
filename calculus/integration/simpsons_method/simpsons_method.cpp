/*
 * Simpsons Rule Numerical Integration Implementations
 *
 * Author: Alejandro Valencia
 * Update: August 17, 2025
 *
 */

#include "calculus/integration/simpsons_method/simpsons_method.h"
#include <stdexcept>

namespace nm
{
namespace calculus
{

double SimpsonsIntegration(const std::function<double(double)>& function,
                           const double a,
                           const double b,
                           const std::int32_t number_of_intervals)
{
    if (number_of_intervals % 2 != 0)
    {
        throw std::invalid_argument(
            "The number of intervals for Simpson's integration must be even!");
    }

    const auto subinterval_length = (b - a) / number_of_intervals;

    double sum{function(a)};
    for (std::int32_t i{1}; i < (number_of_intervals / 2) + 1; ++i)
    {
        if (i < (number_of_intervals / 2))
        {
            sum += (2 * function(a + (2 * i) * subinterval_length) +
                    4 * function(a + (2 * i - 1) * subinterval_length));
        }
        else
        {
            sum += 4 * function(a + (2 * i - 1) * subinterval_length);
        }
    }
    sum += function(b);

    return (subinterval_length / 3.0) * sum;
}

}  // namespace calculus
}  // namespace nm
