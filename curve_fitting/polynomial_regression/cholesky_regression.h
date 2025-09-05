/*
 * Polynomial Regression based on Cholesky Decomposition
 *
 * Author: Alejandro Valencia
 * Update: September 5th, 2025
 *
 */

#ifndef CURVE_FITTING_POLYNOMIAL_REGRESSION_CHOLESKY_REGRESSION_H
#define CURVE_FITTING_POLYNOMIAL_REGRESSION_CHOLESKY_REGRESSION_H

#include "matrix_solvers/utilities.h"

namespace nm
{
namespace curve_fitting
{

matrix::Matrix<double> ConstructVandermondeMatrix(const std::vector<double>& x_values, const std::int32_t degree);
std::vector<double> CholeskyRegression(const matrix::Matrix<double>& A, const matrix::Matrix<double>& b);

}  // namespace curve_fitting

}  // namespace nm

#endif  // CURVE_FITTING_POLYNOMIAL_REGRESSION_CHOLESKY_REGRESSION_H
