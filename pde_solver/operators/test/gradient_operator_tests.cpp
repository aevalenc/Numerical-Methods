/*
 * @file gradient_operator_tests.cpp
 * @brief Unit tests for the GradientOperator class.
 * @details This file contains unit tests for the GradientOperator class, which is part of the C++ CFD library.
 *
 * @date May 2, 2025
 * @author Alejandro Valencia
 */

#include "examples/line_chart/src/data_types/grid.h"
#include "examples/line_chart/src/data_types/spatial_variable.h"
#include "examples/line_chart/src/operators/gradient.h"
#include "examples/line_chart/src/utilities/grid_generator.h"
#include <gtest/gtest.h>

namespace cfd
{

namespace
{

class BaseClassFixture : public testing::Test
{
  public:
    void SetUp() override
    {
        const geometry::Grid grid_ =
            grid_generator_.Create1DLinearGrid(number_of_grid_nodes_, initial_point_x_value_, end_point_x_value_);
        u_.SetGrid(grid_);
        const double wave_speed = 1.0;
        nabla_.SetWaveSpeed(wave_speed);
        // operators::GradientOperator nabla(wave_speed);
        // nabla_ = nabla;
    }

  protected:
    SpatialVariable u_{};
    geometry::GridGenerator grid_generator_{};
    operators::GradientOperator nabla_{};

  public:
    std::int32_t number_of_grid_nodes_{5};
    double initial_point_x_value_{0.0};
    double end_point_x_value_{1.0};
    double left_boundary_condition_{200.0};
    double right_boundary_condition_{400.0};
    double tolerance_{0.001};
};

TEST_F(BaseClassFixture, GivenValidSetup_ExpectCorrectMatrixGeneration)
{
    // Given
    const auto delta_x = (end_point_x_value_ - initial_point_x_value_) / (number_of_grid_nodes_ - 1);

    // Call
    nabla_.GenerateMatrixForSpatialVariable(u_);
    const auto stiffness_matrix = u_.GetStiffnessMatrix();

    // Expect
    EXPECT_NEAR(stiffness_matrix.at(1).at(1), 1.0 / delta_x, tolerance_);
}

}  // namespace

}  // namespace cfd
