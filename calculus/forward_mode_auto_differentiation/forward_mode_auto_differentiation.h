/*
 * Author: Alejandro Valencia
 * Update: March, 9 2025
 */

#include "calculus/data_types/data_types.h"
#include <functional>

#ifndef CALCULUS_FORWARD_MODE_AUTO_DIFFERENTIATION_FORWARD_MODE_AUTO_DIFFERENTIATION_H
#define CALCULUS_FORWARD_MODE_AUTO_DIFFERENTIATION_FORWARD_MODE_AUTO_DIFFERENTIATION_H

namespace nm
{
namespace calculus
{

/// @brief Performs the Forward Mode Automatic Differentiation of a Function at a given point
///
/// @param func: The function to differentiate and evaluate
/// @param x: The point at which to evaluate the derivative
///
/// @return double: the value of the function at the given point
double ForwardModeAutoDifferentiation(const std::function<DualNumber(const DualNumber&)>& func, const double x);

}  // namespace calculus
}  // namespace nm

#endif  // CALCULUS_FORWARD_MODE_AUTO_DIFFERENTIATION_FORWARD_MODE_AUTO_DIFFERENTIATION_H
