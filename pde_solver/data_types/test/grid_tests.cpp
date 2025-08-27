/*
 * @file grid_tests.cpp
 * @brief Unit tests for the Grid class.
 * @details This file contains unit tests for the Grid class, which is part of the C++ CFD library.
 *          The tests cover the basic functionality of the Grid class, including element creation
 *          and display.
 *
 * @date May 2, 2025
 * @author Alejandro Valencia
 */

#include "pde_solver/data_types/grid.h"
#include <gtest/gtest.h>

namespace pde
{

namespace geometry
{
namespace
{
class BaseClassFixture : public testing::Test
{
  protected:
    Grid grid_{};
};

TEST_F(BaseClassFixture, GivenValidGrid_ExpectCorrectDisplay)
{
    // Given
    Node node1(1.0);
    Node node2(2.0);

    Element element({node1, node2});

    std::cout << element << std::endl;  // Should invoke operator<<

    std::vector<Element> elements = {element};
    grid_ = Grid(elements);

    // Act
    const auto& elements_vector = grid_.GetElements();
    for (const auto& element : elements_vector)
    {
        std::cout << "Element: " << element << std::endl;  // Should invoke operator<<
    }

    // Assert
    EXPECT_EQ(elements_vector.size(), 1);
}

}  // namespace
}  // namespace geometry

}  // namespace pde
