/*
 * Main computation file
 *
 * Author: Alejandro Valencia
 * Update: August 19th, 2025
 *
 */

#include "pde_solver/main_solver.h"
#include "pde_solver/data_types/discretization_methods.h"
#include "pde_solver/data_types/finite_difference_schemas.h"
#include "pde_solver/data_types/spatial_variable.h"
#include "pde_solver/data_types/time_variable.h"
#include "pde_solver/operators/gradient.h"
#include "pde_solver/utilities/grid_generator.h"
#include <cstdint>

namespace
{

std::vector<double> Linspace(const double x0, const double xf, const std::int32_t number_of_points)
{
    std::vector<double> x{};
    x.resize(number_of_points);
    const auto dx = (xf - x0) / (number_of_points - 1);
    for (std::int32_t i{0}; i < number_of_points; ++i)
    {
        x.at(i) = x0 + i * dx;
    }
    return x;
}

}  // namespace

Solver::Solver(const double delta_t, const double end_time) : delta_t_(delta_t), end_time_(end_time) {}

void Solver::SetupLinearAdvection()
{
    // Generate Grid
    pde::geometry::GridGenerator grid_generator{};
    const auto grid = grid_generator.Create1DLinearGrid(11, 0.0, 1.0);
    x_ = Linspace(0.0, 1.0, 11);

    // Create Spatial Variable
    pde::SpatialVariable u{};
    u.SetSpatialDiscretizationMethod(pde::SpatialDiscretizationMethod::kFiniteDifferenceMethod);
    u.SetDiscretizationSchema(pde::FiniteDifferenceSchema::kBackwardsDifference);
    u.SetGrid(grid);

    // Apply Operators
    const double wave_speed = 2.0;
    pde::operators::GradientOperator nabla(wave_speed);
    nabla.GenerateMatrixForSpatialVariable(u);

    // Set Time Variable
    pde::TimeVariable tmp{u};
    uu = tmp;
    uu.SetStartTime(0.0);
    uu.SetEndTime(end_time_);
    uu.SetTimeDiscretizationMethod(pde::TimeDiscretizationMethod::kEulerStep);
    uu.SetInitialCondition(std::vector<double>{0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0});

    // Apply Boundary Conditions
    uu.ux_.SetDirichletBoundaryCondition(0, 0);
    uu.ux_.SetDirichletBoundaryCondition(0, 10);

    // Step
    uu.SetTimeStep(delta_t_);
}

void Solver::CallStepOnce()
{
    uu.StepOnce();
}
