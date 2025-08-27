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
#include "pde_solver/operators/laplace.h"
#include "pde_solver/utilities/grid_generator.h"
#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>
#include <utility>

namespace pde
{
namespace
{

struct SteadyStateLinearDiffusionTestParameter
{
    std::int32_t number_of_grid_points{};
    double x0{};
    double xf{};
    std::int32_t max_iterations{};
    double iterative_solver_tolerance{};
    double wave_speed{1.0};
    double forcing_term{};
    std::vector<std::pair<double, std::int32_t>> dirichlet_boundary_pairs{};
    SpatialDiscretizationMethod spatial_discretization_method{SpatialDiscretizationMethod::kFiniteDifferenceMethod};
    FiniteDifferenceSchema spatial_discretization_schema{FiniteDifferenceSchema::kBackwardsDifference};
    MatrixSolverEnum matrix_solver{MatrixSolverEnum::kJacobi};
    double expected_value{};
    std::string test_name{};
};

class SteadyStateLinearDiffusionTestFixture : public ::testing::TestWithParam<SteadyStateLinearDiffusionTestParameter>
{

  public:
    void SetupParameterizedTest(const SteadyStateLinearDiffusionTestParameter& param)
    {

        // Create grid
        grid_ = grid_generator_.Create1DLinearGrid(param.number_of_grid_points, param.x0, param.xf);
        u_.SetGrid(grid_);

        // Create Spatial Variable
        u_.SetSpatialDiscretizationMethod(param.spatial_discretization_method);
        u_.SetDiscretizationSchema(param.spatial_discretization_schema);

        // Apply Operators
        operators::LaplaceOperator delta{};
        delta.GenerateMatrixForSpatialVariable(u_);

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

    void WithDirichletBoundaryConditions(const std::vector<std::pair<double, std::int32_t>>& boundary_pairs)
    {
        if (!boundary_pairs.empty())
        {
            for (const auto& boundary_pair : boundary_pairs)
            {
                // std::cout << "Setting value " << boundary_pair.first << " at index " << boundary_pair.second << "\n";
                u_.SetDirichletBoundaryCondition(boundary_pair.first, boundary_pair.second);
            }
        }
    }

  public:
    geometry::GridGenerator grid_generator_{};
    geometry::Grid grid_{};
    SpatialVariable u_{};

    double tolerance_{0.001};
};

TEST_P(SteadyStateLinearDiffusionTestFixture, GivenNiceFunction_ExpectExactSolution)
{
    // Get Parameter
    const auto param = GetParam();

    // Given
    if (param.forcing_term)
    {
        WithConstantForcing(param.forcing_term, param.number_of_grid_points);
    }
    SetupParameterizedTest(param);

    if (!param.dirichlet_boundary_pairs.empty())
    {
        WithDirichletBoundaryConditions(param.dirichlet_boundary_pairs);
    }

    // Call
    u_.Solve(param.max_iterations, param.iterative_solver_tolerance);

    // Expect
    EXPECT_NEAR(u_.GetDiscretizedVariable().at(param.number_of_grid_points - 2), param.expected_value, tolerance_);
}

INSTANTIATE_TEST_SUITE_P(LinearDiffusionTestFixtureTests,
                         SteadyStateLinearDiffusionTestFixture,
                         testing::Values(
                             SteadyStateLinearDiffusionTestParameter{
                                 .number_of_grid_points = 11,
                                 .xf = 1.0,
                                 .max_iterations = 1000,
                                 .dirichlet_boundary_pairs = {{200, 0}, {400, 10}},
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kCentralDifference,
                                 .matrix_solver = MatrixSolverEnum::kJacobi,
                                 .expected_value = 380.0,
                                 .test_name = "JacobiSolve",
                             },
                             SteadyStateLinearDiffusionTestParameter{
                                 .number_of_grid_points = 11,
                                 .xf = 1.0,
                                 .max_iterations = 1000,
                                 .dirichlet_boundary_pairs = {{200, 0}, {400, 10}},
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kCentralDifference,
                                 .matrix_solver = MatrixSolverEnum::kGaussSeidel,
                                 .expected_value = 380.0,
                                 .test_name = "GaussSeidelSolve",
                             },
                             SteadyStateLinearDiffusionTestParameter{
                                 .number_of_grid_points = 11,
                                 .xf = 1.0,
                                 .max_iterations = 1000,
                                 .dirichlet_boundary_pairs = {{200, 0}, {400, 10}},
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kCentralDifference,
                                 .matrix_solver = MatrixSolverEnum::kConjugateGradient,
                                 .expected_value = 380.0,
                                 .test_name = "ConjugateGradientSolve",
                             },
                             SteadyStateLinearDiffusionTestParameter{
                                 .number_of_grid_points = 11,
                                 .xf = 1.0,
                                 .max_iterations = 1000,
                                 .dirichlet_boundary_pairs = {{200, 0}, {400, 10}},
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kCentralDifference,
                                 .matrix_solver = MatrixSolverEnum::kLUSolve,
                                 .expected_value = 380.0,
                                 .test_name = "LUDecompositionSolve",
                             }),
                         [](const ::testing::TestParamInfo<SteadyStateLinearDiffusionTestParameter>& info)
                             -> std::string { return info.param.test_name; });

}  // namespace
}  // namespace pde
