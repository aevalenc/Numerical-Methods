/*
 * Author: Alejandro Valencia
 * CFD BU Online Course: Laplace Operator
 * Update: April 13, 2024
 */

#include "pde_solver/operators/laplace.h"
#include <algorithm>
#include <vector>

namespace pde
{

namespace operators
{

LaplaceOperator::LaplaceOperator(const SpatialVariable& u_in) : u_(&u_in)
{
    dimension_ = static_cast<std::int8_t>(u_->GetGrid().GetDimension());
    matrix_size_ = static_cast<std::int32_t>(u_->GetGrid().GetNumberOfNodes());
}

void LaplaceOperator::SetSpatialVariable(const SpatialVariable& u_in)
{
    u_ = &u_in;
}

const nm::matrix::Matrix<double> LaplaceOperator::GenerateMatrix()
{
    if (matrix_size_ == 0)
    {
        throw std::exception{};
    }

    nm::matrix::Matrix<double> output_matrix{};
    const std::vector<double> matrix_entries{-1.0, 2.0, -1.0};

    const auto n = static_cast<std::int32_t>(u_->GetGrid().GetNumberOfNodes()) - u_->GetGrid().number_of_boundaries_;

    output_matrix.resize(n);
    for (std::int32_t i{0}; i < n; ++i)
    {
        output_matrix.at(i).resize(n);
        if (i == 0)
        {
            output_matrix.at(i).at(i) = matrix_entries.at(1);
            output_matrix.at(i).at(i + 1) = matrix_entries.at(2);
        }
        else if (i == n - 1)
        {
            output_matrix.at(i).at(i - 1) = matrix_entries.at(2);
            output_matrix.at(i).at(i) = matrix_entries.at(1);
        }
        else
        {
            output_matrix.at(i).at(i - 1) = matrix_entries.at(0);
            output_matrix.at(i).at(i) = matrix_entries.at(1);
            output_matrix.at(i).at(i + 1) = matrix_entries.at(2);
        }
    }
    return output_matrix;
}

void LaplaceOperator::GenerateMatrixForSpatialVariable(SpatialVariable& u)
{
    const auto grid = u.GetGrid();
    matrix_size_ = static_cast<std::int32_t>(grid.GetNumberOfNodes());
    nm::matrix::Matrix<double> output_matrix{};
    const auto elements = u.GetGrid().GetElements();

    output_matrix.resize(matrix_size_);
    if (grid.GetDimension() == 1)
    {
        for (std::int32_t i{0}; i < matrix_size_; ++i)
        {
            output_matrix.at(i).resize(matrix_size_);
            if (i == 0)
            {
                const auto delta_x = std::abs(elements.at(i).GetElement().at(0).GetValues().at(0).value() -
                                              elements.at(i).GetElement().at(1).GetValues().at(0).value());
                output_matrix.at(i).at(i) = constant_diffusion / (delta_x * delta_x) * -2.0;
                output_matrix.at(i).at(i + 1) = constant_diffusion / (delta_x * delta_x);
            }
            else if (i == matrix_size_ - 1)
            {
                const auto delta_x = std::abs(elements.at(i - 1).GetElement().at(0).GetValues().at(0).value() -
                                              elements.at(i - 1).GetElement().at(1).GetValues().at(0).value());
                output_matrix.at(i).at(i - 1) = constant_diffusion / (delta_x * delta_x);
                output_matrix.at(i).at(i) = constant_diffusion / (delta_x * delta_x) * -2.0;
            }
            else
            {
                const auto delta_x = std::abs(elements.at(i).GetElement().at(0).GetValues().at(0).value() -
                                              elements.at(i).GetElement().at(1).GetValues().at(0).value());
                output_matrix.at(i).at(i - 1) = constant_diffusion / (delta_x * delta_x);
                output_matrix.at(i).at(i) = constant_diffusion / (delta_x * delta_x) * -2.0;
                output_matrix.at(i).at(i + 1) = constant_diffusion / (delta_x * delta_x);
            }
        }
        u.SetStiffnessMatrix(output_matrix);
    }
}

}  // namespace operators
}  // namespace pde
