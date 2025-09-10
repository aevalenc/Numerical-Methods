/*
 * Secant method for finding roots of a continuous function.
 *
 * Author: Alejandro Valencia
 * Update: September 10th, 2025
 */

#ifndef ROOT_FINDERS_SECANT_METHOD_SECANT_METHOD_H
#define ROOT_FINDERS_SECANT_METHOD_SECANT_METHOD_H

#include <functional>

namespace nm
{
namespace root_finders
{

double SecantMethod(const std::function<double(double)>& function,
                    const double x0,
                    const double x1,
                    const double tolerance);

}  // namespace root_finders

}  // namespace nm

#endif  // ROOT_FINDERS_SECANT_METHOD_SECANT_METHOD_H
