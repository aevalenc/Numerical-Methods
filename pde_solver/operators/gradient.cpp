/*
 * Author: Alejandro Valencia
 * 12-Steps-To-NS: Gradient Operator
 * Update: May 1, 2025
 */

#include "pde_solver/operators/gradient.h"

namespace pde
{

namespace operators
{

GradientOperator::GradientOperator(const double wave_speed) : wave_speed_(wave_speed) {}

void GradientOperator::SetWaveSpeed(const double wave_speed)
{
    wave_speed_ = wave_speed;
}

void GradientOperator::GenerateMatrixForSpatialVariable(SpatialVariable& u)
{

    // Get spatial variable
    matrix_size_ = u.GetGrid().GetNumberOfNodes();
    const auto grid_dimension = u.GetGrid().GetDimension();

    auto ux = u.GetGrid().GetElementsMutable();

    double delta_x{};
    if (grid_dimension == 1)
    {

        // Generate the gradient matrix
        nm::matrix::Matrix<double> gradient_matrix{};

        gradient_matrix.resize(matrix_size_);

        // Fill the gradient matrix with finite difference coefficients
        for (std::int32_t i = 0; i < matrix_size_; ++i)
        {
            gradient_matrix.at(i).resize(matrix_size_);

            if (i == 0 || (i == matrix_size_ - 1))
            {
                gradient_matrix.at(i).at(i) = 1.0;
                continue;
            }

            delta_x = ux.at(i - 1).GetElement().at(0).GetValues().at(0).value() -
                      ux.at(i).GetElement().at(0).GetValues().at(0).value();
            gradient_matrix.at(i).at(i - 1) = -wave_speed_ / delta_x;
            gradient_matrix.at(i).at(i) = wave_speed_ / delta_x;
            gradient_matrix.at(i).at(i + 1) = 0.0;
        }

        u.SetStiffnessMatrix(gradient_matrix);
    }
}

}  // namespace operators

}  // namespace pde
