/*
 * Author : Alejandro Valencia
 * Project: Newton's Method
 * Update : 12 March, 2023
 */

#include <cstdint>
#include <functional>

#ifndef ROOT_FINDERS_NEWTONS_METHOD_H
#define ROOT_FINDERS_NEWTONS_METHOD_H

namespace nm
{

namespace root_finders
{

double NewtonsMethod(double& x_0,
                     const std::function<double(double)>& function,
                     const std::function<double(double)>& derivative,
                     const double tolerance = 0.001,
                     const std::int32_t max_iterations = 1000);

}  // namespace root_finders

}  // namespace nm

#endif  // ROOT_FINDERS_NEWTONS_METHOD_H
