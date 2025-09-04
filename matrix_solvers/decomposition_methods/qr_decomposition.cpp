/*
 * QR decomposition of a matrix based on the Gram-Schmidt Method
 *
 * Author: Alejandro Valencia
 * Update: November 11, 2023
 */

#include "matrix_solvers/decomposition_methods/qr_decomposition.h"
#include "matrix_solvers/operations/operations.h"

namespace nm
{
namespace matrix
{

std::pair<Matrix<double>, Matrix<double>> QRDecompositionGramSchmidt(const Matrix<double>& A)
{
    const std::int32_t n = static_cast<std::int32_t>(A.at(0).size());

    const auto A_tranpose = A.Transpose();
    Matrix<double> U = A_tranpose;
    Matrix<double> Q = A_tranpose;

    for (std::int32_t k{1}; k < n; ++k)
    {
        for (std::int32_t j{0}; j < k; ++j)
        {
            const auto numerator = Dot(A_tranpose.at(k), U.at(j));
            const auto denominator = Dot(U.at(j), U.at(j));
            const auto projection = ScalarMultiply(numerator / denominator, U.at(j));
            U.at(k) = AddVectors(U.at(k), ScalarMultiply(-1.0, projection));
        }
    }

    for (std::int32_t i{0}; i < n; ++i)
    {
        const auto norm = L2Norm(U.at(i));
        Q.at(i) = ScalarMultiply(1.0 / norm, U.at(i));
    }

    return {Q.Transpose(), MatMult(Q, A)};
}

}  // namespace matrix
}  // namespace nm
