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

std::vector<double> CholeskyRegression(const matrix::Matrix<double>& A, const matrix::Matrix<double>& b)
{
    const auto A_transposed = A.Transpose();
    const auto B = matrix::MatMult(A_transposed, A);
    const auto y = matrix::MatMult(A_transposed, b);

    const auto G = matrix::CholeskyDecomposition(B);
    const auto z = matrix::ForwardSubstitution(G, matrix::ToStdVectorRowBased(y));
    const auto x = matrix::BackwardsSubstitution(G.Transpose(), z);

    return x;
}

}  // namespace curve_fitting
}  // namespace nm
