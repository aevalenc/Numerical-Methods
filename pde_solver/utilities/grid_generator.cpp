///
/// Author: Alejandro Valencia
/// Boston University CFD Course: grid class
/// Update: 16 October, 2022
///

#include "examples/line_chart/src/utilities/grid_generator.h"
#include "examples/line_chart/src/data_types/grid.h"

namespace cfd
{

namespace geometry
{

Grid GridGenerator::Create1DLinearGrid(const std::uint64_t& size, const double& start, const double& end)
{
    std::vector<Element> elements{};
    const auto step_size = (end - start) / (size - 1);

    auto current_point = start;
    for (std::uint64_t idx = 0; idx < size - 1; ++idx)
    {
        Node start_node{current_point};
        if (idx == 0 || idx == (size - 1))
        {
            start_node.SetBoundaryBoolean(true);
        }

        Node end_node{current_point + step_size};
        elements.push_back(std::vector<Node>{start_node, end_node});
        current_point += step_size;
    }

    Grid grid{elements};
    grid.SetDimension(1);
    grid.number_of_boundaries_ = 2;

    return grid;
    // comment for clang-tidy check
}

}  // namespace geometry

}  // namespace cfd
