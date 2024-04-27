/*
 * Author: Alejandro Valencia
 * Optimization Library
 * Update: February 4, 2024
 */

#include <functional>

#ifndef OPTIMIZATION_TERNARY_TERNARY_H
#define OPTIMIZATION_TERNARY_TERNARY_H

namespace nm
{

namespace optimize
{

double ternary_min_search(std::function<double(double)>& function,
                          const double tolerance,
                          const double max_iterations,
                          double lower_bound,
                          double upper_bound);

}  // namespace optimize

}  // namespace nm

#endif  // OPTIMIZATION_TERNARY_TERNARY_H
