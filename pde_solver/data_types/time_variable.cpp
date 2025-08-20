/*
 * Author: Alejandro Valencia
 * 12-Steps-To-Navier-Stokes: Base Spatial Variable Class
 * Update: 9 October, 2022
 *
 * This file serves as the implementation of member functions of the class
 * TimeVariable
 */

#include "pde_solver/data_types/time_variable.h"
#include "pde_solver/data_types/spatial_variable.h"
#include <cassert>
#include <cstdint>
#include <iterator>

namespace cfd
{
namespace
{

std::vector<double> AddVectors(const std::vector<double>& a, const std::vector<double>& b)
{
    std::vector<double> result{a};
    for (std::int32_t i{0}; i < static_cast<int32_t>(a.size()); ++i)
    {
        result[i] += b[i];
    }
    return result;
}

std::vector<double> ScalarMultiply(const double scalar_value, const std::vector<double>& a)
{
    std::vector<double> result{a};
    for (std::int32_t i{0}; i < static_cast<int32_t>(a.size()); ++i)
    {
        result[i] *= scalar_value;
    }
    return result;
}

}  // namespace

TimeVariable::TimeVariable(const SpatialVariable& u)
    : ux_(u), time_discretization_method_(TimeDiscretizationMethod::kInvalid)
{
    u_current_ = ux_.GetDiscretizedVariable();
    u_previous_ = ux_.GetDiscretizedVariable();
}

TimeDiscretizationMethod TimeVariable::GetTimeDiscretizationMethod() const
{
    return time_discretization_method_;
}

void TimeVariable::SetTimeDiscretizationMethod(TimeDiscretizationMethod time_discretization_method)
{
    time_discretization_method_ = time_discretization_method;
}

void TimeVariable::Step(const std::vector<double>& wave_speeds)
{
    assert(start_time_ != end_time_);
    assert(delta_t_ != 0.0);

    const auto number_of_steps = static_cast<std::int32_t>((end_time_ - start_time_) / delta_t_);

    if (time_discretization_method_ == TimeDiscretizationMethod::kEulerStep)
    {
        for (std::int32_t n = 0; n < number_of_steps; ++n)
        {
            for (std::size_t i = 0; i < std::size(u_current_); ++i)
            {
                u_current_[i] = u_previous_[i] + wave_speeds.front() * delta_t_;
            }
        }
    }
}

void TimeVariable::Step()
{
    assert(start_time_ != end_time_);
    assert(delta_t_ != 0.0);

    const auto number_of_steps = static_cast<std::int32_t>((end_time_ - start_time_) / delta_t_);

    if (time_discretization_method_ == TimeDiscretizationMethod::kEulerStep)
    {
        for (std::int32_t n = 0; n < number_of_steps; ++n)
        {
            const auto grad_u = nm::matrix::MatMult(ux_.GetStiffnessMatrix(), u_previous_);
            const auto grad_u_delta_t = ScalarMultiply(delta_t_, grad_u);
            u_current_ = AddVectors(u_previous_, grad_u_delta_t);
        }
    }
}

void TimeVariable::StepOnce()
{
    assert(delta_t_ != 0.0);

    if (time_discretization_method_ == TimeDiscretizationMethod::kEulerStep)
    {
        const auto grad_u = nm::matrix::MatMult(ux_.GetStiffnessMatrix(), u_previous_);
        const auto grad_u_delta_t = ScalarMultiply(delta_t_, grad_u);
        u_current_ = AddVectors(u_previous_, grad_u_delta_t);
        u_previous_ = u_current_;
    }
}

}  // namespace cfd
