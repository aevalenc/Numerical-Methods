/*
 * Author: Alejandro Valencia
 * Update: March, 9 2025
 */

#include "calculus/forward_mode_auto_differentiation/forward_mode_auto_differentiation.h"
#include "calculus/data_types/data_types.h"

namespace nm
{
namespace calculus
{

double ForwardModeAutoDifferentiation(const std::function<DualNumber(const DualNumber&)>& func, const double x)
{
    DualNumber dual_result = func(DualNumber(x, 1));

    return dual_result.dual;
}

}  // namespace calculus
}  // namespace nm
