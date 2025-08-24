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
#include <vector>

namespace pde
{

TimeVariable::TimeVariable(const SpatialVariable& u)
    : ux_(u), time_discretization_method_(TimeDiscretizationMethod::kInvalid)
{
    u_current_ = ux_.GetDiscretizedVariable();
    u_previous_ = ux_.GetDiscretizedVariable();
}

void TimeVariable::InitializeWithSpatialVariable(const SpatialVariable& u)
{
    ux_ = u;
    u_current_ = u.GetDiscretizedVariable();
    u_previous_ = u.GetDiscretizedVariable();
}

void TimeVariable::SetInitialCondition(const std::vector<double>& u_initial)
{
    u_previous_ = u_initial;
    u_current_ = u_previous_;
}

TimeDiscretizationMethod TimeVariable::GetTimeDiscretizationMethod() const
{
    return time_discretization_method_;
}

void TimeVariable::SetTimeDiscretizationMethod(TimeDiscretizationMethod time_discretization_method)
{
    time_discretization_method_ = time_discretization_method;
}

void TimeVariable::SetRightHandSideMatrix(const nm::matrix::Matrix<double>& rhs_matrix)
{
    rhs_matrix_ = rhs_matrix;
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

void TimeVariable::Run()
{
    assert(start_time_ != end_time_);
    assert(delta_t_ != 0.0);
    assert(time_discretization_method_ != TimeDiscretizationMethod::kInvalid);

    const auto number_of_steps = static_cast<std::int32_t>((end_time_ - start_time_) / delta_t_);

    if (time_discretization_method_ == TimeDiscretizationMethod::kEulerStep)
    {
        for (std::int32_t n = 0; n < number_of_steps; ++n)
        {
            const auto rhs_multiplied = nm::matrix::MatMult(rhs_matrix_, u_previous_);
            const auto rhs_delta_t = nm::matrix::ScalarMultiply(delta_t_, rhs_multiplied);
            u_current_ = nm::matrix::AddVectors(u_previous_, rhs_delta_t);
            u_previous_ = u_current_;
        }
    }
    else if (time_discretization_method_ == TimeDiscretizationMethod::kRungeKutta2)
    {
        for (std::int32_t n = 0; n < number_of_steps; ++n)
        {
            const auto rhs_multiplied = nm::matrix::MatMult(rhs_matrix_, u_previous_);
            const auto k1 = nm::matrix::ScalarMultiply(delta_t_, rhs_multiplied);

            const auto u_hat = nm::matrix::AddVectors(u_previous_, k1);
            const auto u_hat_multiplied = nm::matrix::MatMult(rhs_matrix_, u_hat);
            const auto k2 = nm::matrix::ScalarMultiply(delta_t_, u_hat_multiplied);

            const auto k1_plus_k2 = nm::matrix::AddVectors(k1, k2);
            const auto k1_plus_k2_by_2 = nm::matrix::ScalarMultiply(0.5, k1_plus_k2);

            u_current_ = nm::matrix::AddVectors(u_previous_, k1_plus_k2_by_2);
            u_previous_ = u_current_;
        }
    }
    else if (time_discretization_method_ == TimeDiscretizationMethod::kRungeKutta4)
    {
        for (std::int32_t n = 0; n < number_of_steps; ++n)
        {
            const auto k1 = nm::matrix::MatMult(rhs_matrix_, u_previous_);
            const auto k1_x_delta_t_by_2 = nm::matrix::ScalarMultiply(delta_t_ / 2, k1);

            const auto u_hat_k1 = nm::matrix::AddVectors(u_previous_, k1_x_delta_t_by_2);
            const auto k2 = nm::matrix::MatMult(rhs_matrix_, u_hat_k1);

            const auto k2_x_delta_t_by_2 = nm::matrix::ScalarMultiply(delta_t_ / 2, k2);
            const auto u_hat_k2 = nm::matrix::AddVectors(u_previous_, k2_x_delta_t_by_2);
            const auto k3 = nm::matrix::MatMult(rhs_matrix_, u_hat_k2);

            const auto k3_x_delta_t = nm::matrix::ScalarMultiply(delta_t_, k3);
            const auto u_hat_k3 = nm::matrix::AddVectors(u_previous_, k3_x_delta_t);
            const auto k4 = nm::matrix::MatMult(rhs_matrix_, u_hat_k3);

            const auto sum1 = nm::matrix::AddVectors(k1, nm::matrix::ScalarMultiply(2.0, k2));
            const auto sum2 = nm::matrix::AddVectors(sum1, nm::matrix::ScalarMultiply(2.0, k3));
            const auto sum3 = nm::matrix::AddVectors(sum2, k4);

            const auto update = nm::matrix::ScalarMultiply(delta_t_ / 6, sum3);

            u_current_ = nm::matrix::AddVectors(u_previous_, update);
            u_previous_ = u_current_;
        }
    }
}

void TimeVariable::StepOnce()
{
    assert(delta_t_ != 0.0);

    if (time_discretization_method_ == TimeDiscretizationMethod::kEulerStep)
    {
        const auto rhs_multiplied = nm::matrix::MatMult(rhs_matrix_, u_previous_);
        const auto rhs_delta_t = nm::matrix::ScalarMultiply(delta_t_, rhs_multiplied);
        u_current_ = nm::matrix::AddVectors(u_previous_, rhs_delta_t);
        u_previous_ = u_current_;
    }
    else if (time_discretization_method_ == TimeDiscretizationMethod::kRungeKutta2)
    {
        const auto rhs_multiplied = nm::matrix::MatMult(rhs_matrix_, u_previous_);
        const auto k1 = nm::matrix::ScalarMultiply(delta_t_, rhs_multiplied);

        const auto u_hat = nm::matrix::AddVectors(u_previous_, k1);
        const auto u_hat_multiplied = nm::matrix::MatMult(rhs_matrix_, u_hat);
        const auto k2 = nm::matrix::ScalarMultiply(delta_t_, u_hat_multiplied);

        const auto k1_plus_k2 = nm::matrix::AddVectors(k1, k2);
        const auto k1_plus_k2_by_2 = nm::matrix::ScalarMultiply(0.5, k1_plus_k2);

        u_current_ = nm::matrix::AddVectors(u_previous_, k1_plus_k2_by_2);
        u_previous_ = u_current_;
    }
    else if (time_discretization_method_ == TimeDiscretizationMethod::kRungeKutta4)
    {
        const auto k1 = nm::matrix::MatMult(rhs_matrix_, u_previous_);
        const auto k1_x_delta_t_by_2 = nm::matrix::ScalarMultiply(delta_t_ / 2, k1);

        const auto u_hat_k1 = nm::matrix::AddVectors(u_previous_, k1_x_delta_t_by_2);
        const auto k2 = nm::matrix::MatMult(rhs_matrix_, u_hat_k1);

        const auto k2_x_delta_t_by_2 = nm::matrix::ScalarMultiply(delta_t_ / 2, k2);
        const auto u_hat_k2 = nm::matrix::AddVectors(u_previous_, k2_x_delta_t_by_2);
        const auto k3 = nm::matrix::MatMult(rhs_matrix_, u_hat_k2);

        const auto k3_x_delta_t = nm::matrix::ScalarMultiply(delta_t_, k3);
        const auto u_hat_k3 = nm::matrix::AddVectors(u_previous_, k3_x_delta_t);
        const auto k4 = nm::matrix::MatMult(rhs_matrix_, u_hat_k3);

        const auto sum1 = nm::matrix::AddVectors(k1, nm::matrix::ScalarMultiply(2.0, k2));
        const auto sum2 = nm::matrix::AddVectors(sum1, nm::matrix::ScalarMultiply(2.0, k3));
        const auto sum3 = nm::matrix::AddVectors(sum2, k4);

        const auto update = nm::matrix::ScalarMultiply(delta_t_ / 6, sum3);

        u_current_ = nm::matrix::AddVectors(u_previous_, update);
        u_previous_ = u_current_;
    }
}

void TimeVariable::Reset()
{
    u_current_ = {};
    u_previous_ = {};
    rhs_matrix_ = {};
    M_ = {};
}

}  // namespace pde
