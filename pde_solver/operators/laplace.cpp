/*
 * Author: Alejandro Valencia
 * CFD BU Online Course: Laplace Operator
 * Update: April 13, 2024
 */

#include "examples/line_chart/src/operators/laplace.h"
#include <algorithm>
#include <vector>

namespace cfd
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
    matrix_size_ = static_cast<std::int32_t>(u.GetGrid().GetNumberOfNodes());
    nm::matrix::Matrix<double> output_matrix{};
    const std::vector<double> matrix_entries{-1.0, 2.0, -1.0};

    const auto n = static_cast<std::int32_t>(matrix_size_ - u.GetGrid().number_of_boundaries_);

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
    u.SetStiffnessMatrix(output_matrix);
}

}  // namespace operators
}  // namespace cfd
