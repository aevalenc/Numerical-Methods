// Author: Alejandro Valencia
// 12-Steps-To-Navier-Stokes: Base Spatial Variable Class
// Update: 9 October, 2022

/*
 * This file serves as the implementation of member functions of the class
 * SpatialVariable
 */

#include "pde_solver/data_types/spatial_variable.h"
#include "matrix_solvers/iterative_solvers/jacobi.h"
#include "pde_solver/data_types/finite_difference_schemas.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <tuple>

namespace cfd
{

SpatialDiscretizationMethod SpatialVariable::GetSpatialDiscretizationMethod() const
{
    return spatial_discretization_method_;
}

void SpatialVariable::SetSpatialDiscretizationMethod(SpatialDiscretizationMethod spatial_discretization_method)
{
    spatial_discretization_method_ = spatial_discretization_method;
}

void SpatialVariable::SetDiscretizationSchema(FiniteDifferenceSchema discretization_schema)
{
    discretization_schema_ = discretization_schema;
}

void SpatialVariable::SetGrid(const cfd::geometry::Grid& grid)
{
    spatial_grid_ = grid;
    discretized_variable_.resize(spatial_grid_.GetNumberOfNodes());
    K_.resize(spatial_grid_.GetNumberOfNodes() - spatial_grid_.number_of_boundaries_);
    C_.resize(spatial_grid_.GetNumberOfNodes() - spatial_grid_.number_of_boundaries_);
    f_.resize(spatial_grid_.GetNumberOfNodes() - spatial_grid_.number_of_boundaries_);
}

geometry::Grid SpatialVariable::GetGrid() const
{
    return spatial_grid_;
}

void SpatialVariable::SetDirichletBoundaryCondition(const double value, const std::int32_t boundary_index)
{
    if (boundary_index > discretized_variable_.size())
    {
        std::cout << "Tried to access an index beyond the discretized variable max size of "
                  << discretized_variable_.size() << "\n";
        return;
    }

    discretized_variable_.at(boundary_index) = value;
    if (!f_.empty())
    {
        if (boundary_index == 0)
        {
            f_.at(boundary_index) = value;
        }
        else
        {
            f_.back() = value;
        }
    }
    else
    {
        std::cout << "Forcing vector was not properly sized!\n"
                  << "Attemped to assign Dirichlet boundary condition to forcing vector and failed";
        return;
    }
}

void SpatialVariable::SetStiffnessMatrix(nm::matrix::Matrix<double> K)
{
    K_ = K;
}

void SpatialVariable::SetDampingMatrix(nm::matrix::Matrix<double> C)
{
    C_ = C;
}

void SpatialVariable::SetForceVector(std::vector<double> f)
{
    f_ = f;
}

void SpatialVariable::SetMatrixSolver(const MatrixSolverEnum matrix_solver)
{
    matrix_solver_ = matrix_solver;
}

void SpatialVariable::Solve(const std::int32_t max_iterations, const double tolerance)
{
    assert(matrix_solver_ != MatrixSolverEnum::kInvalid);
    assert(!K_.empty());
    assert(!f_.empty());

    std::vector<double>::iterator first_unknown_iterator{discretized_variable_.begin() + 1};
    std::vector<double>::iterator last_unknown_iterator{discretized_variable_.end() - 1};
    std::vector<double> u_subset{first_unknown_iterator, last_unknown_iterator};

    switch (matrix_solver_)
    {
        case MatrixSolverEnum::kJacobi:
            nm::matrix::jacobi(K_, f_, u_subset, max_iterations, tolerance);
            break;
        default:
            break;
    }

    std::ignore = std::copy(std::cbegin(u_subset), std::cend(u_subset), first_unknown_iterator);
}

}  // namespace cfd
