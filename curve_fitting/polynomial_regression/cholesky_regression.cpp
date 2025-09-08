/*
 *
 */

#include "curve_fitting/polynomial_regression/cholesky_regression.h"
#include "matrix_solvers/decomposition_methods/lu_decomposition.h"
#include "matrix_solvers/direct_solvers/backwards_substitution.h"
#include "matrix_solvers/direct_solvers/forward_substitution.h"
#include "matrix_solvers/operations/operations.h"

namespace nm
{

namespace curve_fitting
{

matrix::Matrix<double> ConstructVandermondeMatrix(const std::vector<double>& x_values, const std::int32_t degree)
{
    const auto n = static_cast<std::int32_t>(x_values.size());
    matrix::Matrix<double> A(n, degree + 1);

    for (std::int32_t i = 0; i < n; ++i)
    {
        double value = 1.0;
        for (std::int32_t j = 0; j < degree + 1; ++j)
        {
            A.at(i).at(j) = value;
            value *= x_values[i];
        }
    }
    return A;
}

std::vector<double> CholeskyRegression(const std::vector<double>& x_values,
                                       const std::vector<double>& y_values,
                                       const std::int32_t degree)
{
    const auto A = ConstructVandermondeMatrix(x_values, degree);
    const auto A_transposed = A.Transpose();
    const auto B = matrix::MatMult(A_transposed, A);
    const auto y = matrix::MatMult(A_transposed, y_values);

    const auto G = matrix::CholeskyDecomposition(B);
    const auto z = matrix::ForwardSubstitution(G, y);
    const auto x = matrix::BackwardsSubstitution(G.Transpose(), z);

    return x;
}

}  // namespace curve_fitting
}  // namespace nm
