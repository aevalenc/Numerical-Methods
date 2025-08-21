/*
 * Linear Advection Tests
 *
 * Author: Alejandro Valencia
 * Update: August 21, 2025
 *
 */

#include "gtest/gtest.h"
#include "pde_solver/data_types/discretization_methods.h"
#include "pde_solver/data_types/finite_difference_schemas.h"
#include "pde_solver/data_types/grid.h"
#include "pde_solver/data_types/spatial_variable.h"
#include "pde_solver/data_types/time_variable.h"
#include "pde_solver/operators/gradient.h"
#include "pde_solver/utilities/grid_generator.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>

namespace pde
{
namespace
{

struct LinearAdvectionTestParameter
{
    std::int32_t number_of_grid_points{};
    double x0{};
    double xf{};
    double start_time{};
    double end_time{};
    double delta_t{};
    double wave_speed{1.0};
    SpatialDiscretizationMethod spatial_discretization_method{SpatialDiscretizationMethod::kFiniteDifferenceMethod};
    FiniteDifferenceSchema spatial_discretization_schema{FiniteDifferenceSchema::kBackwardsDifference};
    TimeDiscretizationMethod time_discretization_method{TimeDiscretizationMethod::kEulerStep};
    std::vector<double> initial_condition{};
    std::ptrdiff_t offset{1};
    std::ptrdiff_t wave_width{3};
    std::ptrdiff_t wave_height{1};
};

class LinearAdvectionTestFixture : public ::testing::TestWithParam<LinearAdvectionTestParameter>
{

  public:
    void SetupParameterizedTest(const LinearAdvectionTestParameter& param)
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

        // Set Time Variable
        uu_.InitializeWithSpatialVariable(u_);
        uu_.SetTimeDiscretizationMethod(param.time_discretization_method);

        std::vector<double> initial_condition{};
        initial_condition.resize(param.number_of_grid_points);
        std::fill(initial_condition.begin() + param.offset,
                  initial_condition.begin() + param.offset + param.wave_width,
                  param.wave_height);
        uu_.SetInitialCondition(initial_condition);

        // Apply Boundary Conditions
        uu_.ux_.SetDirichletBoundaryCondition(0, 0);
        uu_.ux_.SetDirichletBoundaryCondition(0, uu_.GetTimeVariable().size() - 1);

        // Set time parameters
        uu_.SetStartTime(param.start_time);
        uu_.SetEndTime(param.end_time);
        uu_.SetTimeStep(param.delta_t);
    }

  public:
    geometry::GridGenerator grid_generator_{};
    geometry::Grid grid_{};
    SpatialVariable u_{};
    TimeVariable uu_{};

    double tolerance_{0.001};
};

TEST_P(LinearAdvectionTestFixture, GivenSquareWaveAndCFLEqualToOne_ExpectNoNumericalDiffusion)
{
    // Get Parameter
    const auto param = GetParam();

    SetupParameterizedTest(param);

    // Call and Expect
    for (std::int32_t t{}; t < static_cast<std::int32_t>((param.end_time - param.start_time) / param.delta_t); ++t)
    {
        uu_.StepOnce();
        const auto max_value = std::max_element(uu_.GetTimeVariable().cbegin(), uu_.GetTimeVariable().cend());
        if (max_value != uu_.GetTimeVariable().cend())
        {
            EXPECT_NEAR(*max_value, param.wave_height, tolerance_);
        }
        else
        {
            FAIL();
        }
    }
}

INSTANTIATE_TEST_SUITE_P(LinearAdvectionTestFixtureTests,
                         LinearAdvectionTestFixture,
                         testing::Values(
                             LinearAdvectionTestParameter{
                                 .number_of_grid_points = 11,
                                 .xf = 1.0,
                                 .end_time = 0.8,
                                 .delta_t = 0.1,
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,
                                 .time_discretization_method = TimeDiscretizationMethod::kEulerStep,
                             },
                             LinearAdvectionTestParameter{
                                 .number_of_grid_points = 101,
                                 .xf = 1.0,
                                 .end_time = 0.8,
                                 .delta_t = 0.01,
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,
                                 .time_discretization_method = TimeDiscretizationMethod::kEulerStep,
                             },
                             LinearAdvectionTestParameter{
                                 .number_of_grid_points = 101,
                                 .xf = 1.0,
                                 .end_time = 0.4,
                                 .delta_t = 0.005,
                                 .wave_speed = 2.0,
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,
                                 .time_discretization_method = TimeDiscretizationMethod::kEulerStep,
                             }));

class NonSingularCFLFixture : public LinearAdvectionTestFixture
{
};

TEST_P(NonSingularCFLFixture, GivenSquareWaveAndCFLNotEqualToOne_ExpectNumericalDiffusion)
{
    // Get Parameter
    const auto param = GetParam();
    SetupParameterizedTest(param);

    // Call
    uu_.Run();

    // Expect
    const auto max_value = std::max_element(uu_.GetTimeVariable().cbegin(), uu_.GetTimeVariable().cend());
    if (max_value != uu_.GetTimeVariable().cend())
    {
        EXPECT_LT(*max_value, param.wave_height);
    }
    else
    {
        FAIL();
    }
}

INSTANTIATE_TEST_SUITE_P(LinearAdvectionWithCFLLowerThanOneTests,
                         NonSingularCFLFixture,
                         testing::Values(
                             LinearAdvectionTestParameter{
                                 .number_of_grid_points = 11,
                                 .xf = 1.0,
                                 .end_time = 0.8,
                                 .delta_t = 0.01,
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,
                                 .time_discretization_method = TimeDiscretizationMethod::kEulerStep,
                             },
                             LinearAdvectionTestParameter{
                                 .number_of_grid_points = 101,
                                 .xf = 1.0,
                                 .end_time = 0.8,
                                 .delta_t = 0.001,
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,
                                 .time_discretization_method = TimeDiscretizationMethod::kEulerStep,
                             },
                             LinearAdvectionTestParameter{
                                 .number_of_grid_points = 101,
                                 .xf = 1.0,
                                 .end_time = 0.4,
                                 .delta_t = 0.0025,
                                 .wave_speed = 2.0,
                                 .spatial_discretization_method = SpatialDiscretizationMethod::kFiniteDifferenceMethod,
                                 .spatial_discretization_schema = FiniteDifferenceSchema::kBackwardsDifference,
                                 .time_discretization_method = TimeDiscretizationMethod::kEulerStep,
                             }));

}  // namespace
}  // namespace pde
