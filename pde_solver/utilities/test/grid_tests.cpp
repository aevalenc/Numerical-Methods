///
/// Author: Alejandro Valencia
/// Grid Generator tests
/// Update: 20 November, 2021
///

#include "pde_solver/data_types/grid.h"
#include "pde_solver/utilities/grid_generator.h"
#include <gtest/gtest.h>

namespace pde
{

namespace geometry
{

namespace
{

TEST(OneDimensionLinearGridTests, GivenValidStartAndEnd_ExpectValidGrid)
{
    // Given
    GridGenerator grid_generator{};
    const std::uint64_t size{11};
    const double start{0.0};
    const double end{1.0};
    const double tolerance{0.001};

    // Call
    const auto result = grid_generator.Create1DLinearGrid(size, start, end);
    const auto first_node = result.GetElements().at(0).GetElement().front();
    const auto first_node_x_value = first_node.GetValues().front();

    ASSERT_TRUE(first_node_x_value.has_value());

    // Expect
    EXPECT_EQ(result.GetSize(), 11);
    EXPECT_EQ(result.GetDimension(), 1);
    EXPECT_NEAR(*first_node_x_value, 0.0, tolerance);
}

}  // namespace

}  // namespace geometry

}  // namespace pde
