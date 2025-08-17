/*
 * Simpsons method for numerical integration.
 *
 * Author: Alejandro Valencia
 * Update: August 14, 2025
 */

#ifndef CALCULUS_INTEGRATION_SIMPSONS_METHOD_SIMPSONS_METHOD_H
#define CALCULUS_INTEGRATION_SIMPSONS_METHOD_SIMPSONS_METHOD_H

#include <cstdint>
#include <functional>

namespace nm
{
namespace calculus
{

double SimpsonsIntegration(const std::function<double(double)>& function,
                           const double a,
                           const double b,
                           const std::int32_t number_of_intervals);

}  // namespace calculus
}  // namespace nm

#endif  // CALCULUS_INTEGRATION_SIMPSONS_METHOD_SIMPSONS_METHOD_H
