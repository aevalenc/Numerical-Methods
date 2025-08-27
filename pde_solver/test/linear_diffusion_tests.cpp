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
#include "pde_solver/data_types/time_variable.h"
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
    double start_time{};
    double end_time{};
    double delta_t{};
    double constant_diffusion{1.0};
    std::ptrdiff_t offset{1};
    std::ptrdiff_t wave_width{3};
    double wave_height{1};
    double forcing_term{};
    std::vector<std::pair<double, std::int32_t>> dirichlet_boundary_pairs{};
    SpatialDiscretizationMethod spatial_discretization_method{SpatialDiscretizationMethod::kFiniteDifferenceMethod};
    FiniteDifferenceSchema spatial_discretization_schema{FiniteDifferenceSchema::kBackwardsDifference};
    TimeDiscretizationMethod time_discretization_method{TimeDiscretizationMethod::kEulerStep};
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
        delta.SetConstantDiffusion(param.constant_diffusion);
        delta.GenerateMatrixForSpatialVariable(u_);

        if (!param.dirichlet_boundary_pairs.empty())
        {
            for (const auto& boundary_pair : param.dirichlet_boundary_pairs)
            {
                u_.SetDirichletBoundaryCondition(boundary_pair.first, boundary_pair.second);
            }
        }

        // Create Time Variable
        uu_.InitializeWithSpatialVariable(u_);
        uu_.SetTimeDiscretizationMethod(param.time_discretization_method);

        std::vector<double> initial_condition{};
        initial_condition.resize(param.number_of_grid_points);
        std::fill(initial_condition.begin() + param.offset,
                  initial_condition.begin() + param.offset + param.wave_width,
                  param.wave_height);
        uu_.SetInitialCondition(initial_condition);

        // Set time parameters
        uu_.SetStartTime(param.start_time);
        uu_.SetEndTime(param.end_time);
        uu_.SetTimeStep(param.delta_t);

        // Construct right hand side
        uu_.SetRightHandSideMatrix(uu_.ux_.GetStiffnessMatrix());
    }

    void WithConstantForcing(const double forcing, const std::int32_t number_of_nodes)
    {
        std::vector<double> f{};
        f.resize(number_of_nodes);
        std::fill(f.begin(), f.end(), forcing);
        u_.SetForceVector(f);
    }

    void WithDirichletBoundaryConditions(const std::vector<std::pair<double, std::int32_t>>& boundary_pairs) {}

  public:
    geometry::GridGenerator grid_generator_{};
    geometry::Grid grid_{};
    SpatialVariable u_{};
    TimeVariable uu_{};

    double tolerance_{0.001};
};

TEST_P(SteadyStateLinearDiffusionTestFixture, GivenSqaureInitialization_ExpectValidDiffusionAtMidpoint)
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
    uu_.Run();

    // Expect
    const auto midpoint = param.number_of_grid_points / 2;
    EXPECT_NEAR(uu_.GetTimeVariable().at(midpoint), param.expected_value, tolerance_);
}

INSTANTIATE_TEST_SUITE_P(LinearDiffusionTestFixtureTests,
                         SteadyStateLinearDiffusionTestFixture,
                         testing::Values(
                             // clang-format off
                             SteadyStateLinearDiffusionTestParameter{
                                .number_of_grid_points = 21,
                                .xf = 2.0,
                                .end_time = 0.51,
                                .delta_t = 0.01,
                                .constant_diffusion = 0.1,
                                .offset = 5,
                                .wave_width = 6,
                                .wave_height = 1.0,
                                .dirichlet_boundary_pairs = {{0, 0}, {0, 20}},
                                .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                .spatial_discretization_schema = FiniteDifferenceSchema::kCentralDifference,
                                .time_discretization_method = TimeDiscretizationMethod::kEulerStep,
                                .expected_value = 0.5208,
                                .test_name = "EulerStep",
                            },
                            SteadyStateLinearDiffusionTestParameter{
                                .number_of_grid_points = 21,
                                .xf = 2.0,
                                .end_time = 0.51,
                                .delta_t = 0.01,
                                .constant_diffusion = 0.1,
                                .offset = 5,
                                .wave_width = 6,
                                .wave_height = 1.0,
                                .dirichlet_boundary_pairs = {{0, 0}, {0, 20}},
                                .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                .spatial_discretization_schema = FiniteDifferenceSchema::kCentralDifference,
                                .time_discretization_method = TimeDiscretizationMethod::kRungeKutta2,
                                .expected_value = 0.5208,
                                .test_name = "SecondOrderRungaKutta",
                            },
                            SteadyStateLinearDiffusionTestParameter{
                                .number_of_grid_points = 21,
                                .xf = 2.0,
                                .end_time = 0.51,
                                .delta_t = 0.01,
                                .constant_diffusion = 0.1,
                                .offset = 5,
                                .wave_width = 6,
                                .wave_height = 1.0,
                                .dirichlet_boundary_pairs = {{0, 0}, {0, 20}},
                                .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                .spatial_discretization_schema = FiniteDifferenceSchema::kCentralDifference,
                                .time_discretization_method = TimeDiscretizationMethod::kRungeKutta4,
                                .expected_value = 0.5208,
                                .test_name = "FourthOrderRungaKutta",
                            }
                            // clang-format on 
                        ),
                         [](const ::testing::TestParamInfo<SteadyStateLinearDiffusionTestParameter>& info)
                             -> std::string { return info.param.test_name; });

}  // namespace
}  // namespace pde
