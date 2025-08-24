/*
 * @brief Unit tests for the SpatialVariable class.
 * @details This file contains unit tests for the SpatialVariable class, which is part of the C++ CFD library.
 *          The tests cover the basic functionality of the SpatialVariable class, including
 *          setting and getting the spatial discretization method.
 *          The tests also include copy and move constructors and assignment operators.
 * @date May 2, 2025
 * @author Alejandro Valencia
 */

#include "pde_solver/data_types/discretization_methods.h"
#include "pde_solver/data_types/finite_difference_schemas.h"
#include "pde_solver/data_types/grid.h"
#include "pde_solver/data_types/spatial_variable.h"
#include "pde_solver/data_types/time_variable.h"
#include "pde_solver/operators/gradient.h"
#include "pde_solver/utilities/grid_generator.h"
#include <cstdint>
#include <gtest/gtest.h>

namespace pde
{

namespace
{

class BaseClassFixture : public testing::Test
{
  public:
    SpatialVariable u_{};
    TimeVariable uu_{};
    geometry::GridGenerator grid_generator_{};
    operators::GradientOperator nabla_{};

  public:
    void SetUp() override
    {
        const geometry::Grid grid_ =
            grid_generator_.Create1DLinearGrid(number_of_grid_nodes_, initial_point_x_value_, end_point_x_value_);
        u_.SetGrid(grid_);
        u_.SetSpatialDiscretizationMethod(SpatialDiscretizationMethod::kFiniteDifferenceMethod);
        u_.SetDiscretizationSchema(FiniteDifferenceSchema::kBackwardsDifference);

        // Apply given gradient
        const double wave_speed = 1.0;
        pde::operators::GradientOperator nabla(wave_speed);
        nabla.GenerateMatrixForSpatialVariable(u_);

        // Given time variable
        uu_.InitializeWithSpatialVariable(u_);
        uu_.SetStartTime(0.0);
        uu_.SetEndTime(10.0);
        uu_.SetInitialCondition(std::vector<double>{0, 1, 1, 0, 0});

        // Given Boundary Conditions
        uu_.ux_.SetDirichletBoundaryCondition(left_boundary_condition_, 0);
        uu_.ux_.SetDirichletBoundaryCondition(right_boundary_condition_, number_of_grid_nodes_ - 1);

        // Given time step
        uu_.SetTimeStep(time_step_);

        // Construct right hand side
        const auto negative_gradient = nm::matrix::ScalarMultiply(-1.0, uu_.ux_.GetStiffnessMatrix());
        uu_.SetRightHandSideMatrix(negative_gradient);
    }

  public:
    std::int32_t number_of_grid_nodes_{5};
    double initial_point_x_value_{0.0};
    double end_point_x_value_{1.0};
    double left_boundary_condition_{0.0};
    double right_boundary_condition_{0.0};
    double time_step_{0.1};
};

TEST_F(BaseClassFixture, GivenSquareWaveInitialization_WithEulerStep_ExpectValidSingleStep)
{
    // When
    uu_.SetTimeDiscretizationMethod(TimeDiscretizationMethod::kEulerStep);

    // Call Advance One Step
    uu_.StepOnce();

    // Expect
    EXPECT_NEAR(uu_.GetTimeVariable().at(1), 0.6, 0.001);
    EXPECT_NEAR(uu_.GetTimeVariable().at(2), 1.0, 0.001);
}

TEST_F(BaseClassFixture, DISABLED_GivenSquareWaveInitialization_WithSecondOrderRK_ExpectValidSingleStep)
{
    // When
    uu_.SetTimeDiscretizationMethod(TimeDiscretizationMethod::kEulerStep);
    uu_.SetTimeStep(0.25);

    // Call Advance One Step
    uu_.StepOnce();

    // Expect
    EXPECT_NEAR(uu_.GetTimeVariable().at(1), 0.0, 0.001);
    EXPECT_NEAR(uu_.GetTimeVariable().at(2), 1.0, 0.001);
}

}  // namespace

}  // namespace pde
