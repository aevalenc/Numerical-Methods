/*
 * Secant method for finding roots of a system of nonlinear equations.
 *
 * Author: Alejandro Valencia
 * Update: October 20th, 2025
 */

#ifndef ROOT_FINDERS_SECANT_METHOD_MULTIVAR_SECANT_METHOD_H
#define ROOT_FINDERS_SECANT_METHOD_MULTIVAR_SECANT_METHOD_H

#include <cstdint>
#include <functional>
#include <vector>

namespace nm
{
namespace root_finders
{

std::vector<double> MultiVarSecantMethod(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                         const std::vector<double>& x0,
                                         const std::vector<double>& x1,
                                         const std::vector<double>& x2,
                                         const double tolerance = 1e-6,
                                         const std::int32_t max_iterations = 1000);

}  // namespace root_finders

}  // namespace nm

#endif  // ROOT_FINDERS_SECANT_METHOD_MULTIVAR_SECANT_METHOD_H
