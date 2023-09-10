/*
 * Author : Alejandro Valencia
 * Project: Newton's Method
 * Update : 12 March, 2023
 */

#include <functional>
#include <limits>

namespace nm
{

namespace polysolver
{

double NewtonsMethod(double& x_0,
                     const std::function<double(double)>& function,
                     const std::function<double(double)>& derivative,
                     const double tolerance = 0.001,
                     const std::int32_t max_iterations = 1000);

}

}  // namespace nm
