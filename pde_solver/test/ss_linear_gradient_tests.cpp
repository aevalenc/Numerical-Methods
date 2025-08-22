/*
 * Steady State Linear Gradient Tests (Finding equation of a line)
 *
 * Author: Alejandro Valencia
 * Update: August 22, 2025
 *
 */

#include "gtest/gtest.h"
#include "pde_solver/data_types/discretization_methods.h"
#include "pde_solver/data_types/finite_difference_schemas.h"
#include "pde_solver/data_types/grid.h"
#include "pde_solver/data_types/spatial_variable.h"
#include "pde_solver/operators/gradient.h"
#include "pde_solver/utilities/grid_generator.h"
#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>

namespace pde
{
namespace
{

struct SteadyStateLinearAdvectionTestParameter
{
    std::int32_t number_of_grid_points{};
    double x0{};
    double xf{};
    std::int32_t max_iterations{};
    double iterative_solver_tolerance{};
    double wave_speed{1.0};
    double forcing_term{};
    double dirichlet_boundary_value{};
    std::int32_t boundary_index{};
    SpatialDiscretizationMethod spatial_discretization_method{SpatialDiscretizationMethod::kFiniteDifferenceMethod};
    FiniteDifferenceSchema spatial_discretization_schema{FiniteDifferenceSchema::kBackwardsDifference};
    MatrixSolverEnum matrix_solver{MatrixSolverEnum::kJacobi};
    double expected_value{};
};

class SteadyStateLinearAdvectionTestFixture : public ::testing::TestWithParam<SteadyStateLinearAdvectionTestParameter>
{

  public:
    void SetupParameterizedTest(const SteadyStateLinearAdvectionTestParameter& param)
    {

        // Create grid
        grid_ = grid_generator_.Create1DLinearGrid(param.number_of_grid_points, param.x0, param.xf);

        // Create Spatial Variable
        u_.SetSpatialDiscretizationMethod(param.spatial_discretization_method);
        u_.SetDiscretizationSchema(param.spatial_discretization_schema);
        u_.SetGrid(grid_);

        // Apply Operators
        operators::GradientOperator nabla(param.wave_speed);
        nabla.GenerateMatrixForSpatialVariable(u_);

        // Boundary Condition
        u_.SetDirichletBoundaryCondition(param.dirichlet_boundary_value, param.boundary_index);

        // Solver
        u_.SetMatrixSolver(param.matrix_solver);
    }
    void WithConstantForcing(const double forcing, const std::int32_t number_of_nodes)
    {
        std::vector<double> f{};
        f.resize(number_of_nodes);
        std::fill(f.begin(), f.end(), forcing);
        u_.SetForceVector(f);
    }

  public:
    geometry::GridGenerator grid_generator_{};
    geometry::Grid grid_{};
    SpatialVariable u_{};

    double tolerance_{0.001};
};

TEST_P(SteadyStateLinearAdvectionTestFixture, GivenSquareWaveAndCFLEqualToOne_ExpectNoNumericalDiffusion)
{
    // Get Parameter
    const auto param = GetParam();

    // Given
    if (param.forcing_term)
    {
        WithConstantForcing(param.forcing_term, param.number_of_grid_points);
    }
    SetupParameterizedTest(param);

    // Call
    u_.Solve(param.max_iterations, param.iterative_solver_tolerance);

    // Expect
    EXPECT_NEAR(u_.GetDiscretizedVariable().back(), param.expected_value, tolerance_);
    nm::matrix::PrintVector(u_.GetDiscretizedVariable());
    // EXPECT_TRUE(true);
}

INSTANTIATE_TEST_SUITE_P(
    LinearAdvectionTestFixtureTests,
    SteadyStateLinearAdvectionTestFixture,
    testing::Values(
        //  SteadyStateLinearAdvectionTestParameter{
        //      .number_of_grid_points = 11,
        //      .xf = 1.0,
        //      .max_iterations = 1000,
        //      .delta_t = 0.1,
        //      .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
        //      .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,

        //  },
        //  SteadyStateLinearAdvectionTestParameter{
        //      .number_of_grid_points = 101,
        //      .xf = 1.0,
        //      .end_time = 0.8,
        //      .delta_t = 0.01,
        //      .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
        //      .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,

        //  },
        SteadyStateLinearAdvectionTestParameter{
            .number_of_grid_points = 11,
            .xf = 1.0,
            .max_iterations = 1000,
            .wave_speed = 1.0,
            .forcing_term = 7.0,
            .dirichlet_boundary_value = 3.0,
            .boundary_index = 0,
            .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
            .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,
            .matrix_solver = MatrixSolverEnum::kJacobi,
            .expected_value = 10.0}));

}  // namespace
}  // namespace pde
