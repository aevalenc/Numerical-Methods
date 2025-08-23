/*
 * Author: Alejandro Valencia
 * CFD BU Online Course: Laplace Operator
 * Update: April 13, 2024
 */

#ifndef PDE_SOLVER_OPERATORS_LAPLACE_H
#define PDE_SOLVER_OPERATORS_LAPLACE_H

#include "matrix_solvers/utilities.h"
#include "pde_solver/data_types/spatial_variable.h"
#include <cstdint>

namespace pde
{

namespace operators
{

class LaplaceOperator
{
  public:
    const nm::matrix::Matrix<double> GenerateMatrix();
    void GenerateMatrixForSpatialVariable(SpatialVariable& u);
    void SetSpatialVariable(const SpatialVariable& u_in);

  public:
    LaplaceOperator() {};
    LaplaceOperator(const SpatialVariable& u_in);

  private:
    const SpatialVariable* u_{};
    std::int8_t dimension_{1};
    std::int32_t matrix_size_{};
    double constant_diffusion{1.0};
};

}  // namespace operators

}  // namespace pde

#endif  // PDE_SOLVER_OPERATORS_LAPLACE_H
