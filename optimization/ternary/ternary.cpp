/*
 * Author: Alejandro Valencia
 * Optimization Library
 * Update: February 4, 2024
 */

#include "optimization/ternary/ternary.h"
#include <iostream>

namespace nm
{

namespace optimize
{

double ternary_min_search(std::function<double(double)>& function,
                          const double tolerance,
                          const double max_iterations,
                          double lower_bound,
                          double upper_bound)
{
    // Remaining Declarations
    double c;
    double d, residual, fc, fd;

    // Loop until convergence
    for (size_t iteration = 0; iteration < max_iterations; ++iteration)
    {

        // Calculate Inner Intervals
        c = (2.0 * lower_bound + upper_bound) / 3.0;
        d = (lower_bound + 2.0 * upper_bound) / 3.0;

        // Evaluate Function at Inner Intervals
        fc = function(c);
        fd = function(d);

        // Check Which Section to Eliminate
        if (fc < fd)
        {
            upper_bound = d;
        }
        else
        {
            lower_bound = c;
        }

        // Calculate Minimum Location
        residual = upper_bound - lower_bound;

        if (residual < tolerance)
        {
            std::cout << "Ternary search converged in " << iteration + 1 << " iterations\n";
            return (upper_bound + lower_bound) / 2.0;
        }
        if (iteration == max_iterations)
        {
            std::cout << "WARNING: Ternary search reached max iterations\n";
        }
    }
    return (upper_bound + lower_bound) / 2.0;
}

}  // namespace optimize

}  // namespace nm
