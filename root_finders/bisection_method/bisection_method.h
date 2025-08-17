/*
 * Bisection method for finding roots of a continuous function.
 *
 * Author: Alejandro Valencia
 * Update: August 14, 2025
 */

#ifndef ROOT_FINDERS_BISECTION_METHOD_BISECTION_METHOD_H
#define ROOT_FINDERS_BISECTION_METHOD_BISECTION_METHOD_H

#include <functional>

namespace nm
{
namespace root_finders
{

double BisectionMethod(const std::function<double(double)>& function,
                       const double a,
                       const double b,
                       const double tolerance);

}  // namespace root_finders

}  // namespace nm

#endif  // ROOT_FINDERS_BISECTION_METHOD_BISECTION_METHOD_H
