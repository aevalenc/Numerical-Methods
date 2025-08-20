/*
 * @file laplace_operator_tests.cpp
 * @brief Unit tests for the LaplaceOperator class.
 * @details This file contains unit tests for the LaplaceOperator class, which is part of the C++ CFD library.
 *
 * @date May 2, 2025
 * @author Alejandro Valencia
 */

#include "examples/line_chart/src/data_types/grid.h"
#include "examples/line_chart/src/data_types/spatial_variable.h"
#include "examples/line_chart/src/operators/laplace.h"
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
        operators::LaplaceOperator delta(u_);
        delta_ = std::move(delta);
    }

  protected:
    SpatialVariable u_{};
    geometry::GridGenerator grid_generator_{};
    operators::LaplaceOperator delta_;

  public:
    std::uint64_t number_of_grid_nodes_{5};
    double initial_point_x_value_{0.0};
    double end_point_x_value_{1.0};
    double left_boundary_condition_{200.0};
    double right_boundary_condition_{400.0};
    double tolerance_{0.001};
};

TEST_F(BaseClassFixture, GivenValidSetup_ExpectCorrectMatrixGeneration)
{
    const auto result = delta_.GenerateMatrix();
    nm::matrix::PrintMatrix(result);
    EXPECT_NEAR(result.at(0).at(0), 2.0, tolerance_);
}

}  // namespace

}  // namespace cfd
