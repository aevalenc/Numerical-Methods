///
/// Author: Alejandro Valencia
/// Boston University CFD Course: grid class
/// Update: 16 October, 2022
///

#ifndef PDE_SOLVER_UTILITIES_GRID_GENERATOR_H
#define PDE_SOLVER_UTILITIES_GRID_GENERATOR_H

#include "pde_solver/data_types/grid.h"

namespace pde
{

namespace geometry
{

class GridGenerator
{
  public:
    Grid GetGrid() { return grid_; };
    Grid Create1DLinearGrid(const std::uint64_t& size, const double& start, const double& end);

  private:
    Grid grid_{};
};

}  // namespace geometry

}  // namespace pde

#endif  // PDE_SOLVER_UTILITIES_GRID_GENERATOR_H
