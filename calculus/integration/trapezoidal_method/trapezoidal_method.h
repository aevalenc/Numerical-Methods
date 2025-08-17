/*
 * Trapezoidal method for numerical integration.
 *
 * Author: Alejandro Valencia
 * Update: August 14, 2025
 */

#ifndef CALCULUS_INTEGRATION_TRAPEZOIDAL_METHOD_TRAPEZOIDAL_METHOD_H
#define CALCULUS_INTEGRATION_TRAPEZOIDAL_METHOD_TRAPEZOIDAL_METHOD_H

#include <cstdint>
#include <functional>

namespace nm
{
namespace calculus
{

double TrapezoidalIntegration(const std::function<double(double)>& function,
                              const double a,
                              const double b,
                              const std::int32_t n);

}  // namespace calculus
}  // namespace nm

#endif  // CALCULUS_INTEGRATION_TRAPEZOIDAL_METHOD_TRAPEZOIDAL_METHOD_H
