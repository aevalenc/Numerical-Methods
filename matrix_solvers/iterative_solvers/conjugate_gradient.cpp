/*
 * Author: Alejandro Valencia
 * Update: October 8, 2023
 */

#include "matrix_solvers/iterative_solvers/conjugate_gradient.h"
// #include <algorithm>
// #include <cmath>
// #include <cstdint>
// #include <numeric>

namespace nm
{

namespace matrix
{

namespace
{

bool IsSolutionConverged(double residual,
                         const double tolerance,
                         const std::int32_t iteration,
                         std::int32_t max_iterations)
{
    if (residual <= tolerance)
    {
        // clang-format off
        #ifdef PRINT_DEBUG
            std::cerr << "Conjugate gradient solver converged in " << iteration << " iterations\n";
        #endif
        //clang-format on
        return true;
    }

    if (iteration == max_iterations)
    {
        // clang-format off
        #ifdef PRINT_DEBUG
            std::cerr << "Conjugate gradient solver reached max iterations with a l2norm residual: " << residual  << "\n";
        #endif
        //clang-format on
    }
    
    return false;
}

}  // namespace

void ConjugateGradient(const Matrix<double>& A,
                       const std::vector<double>& b,
                       std::vector<double>& x,
                       const double tolerance,
                       const std::int32_t max_iterations)
{

    const auto n = static_cast<std::int32_t>(b.size());
    auto residual_vector = CalculateResidual(A, b, x, n);
    auto residual = L2Norm(residual_vector);

    for (std::int32_t iteration{0}; iteration < max_iterations; ++iteration)
    {
        ++iteration;
        if (IsSolutionConverged(residual, tolerance, iteration, max_iterations))
        {
            return;
        }

        auto p = residual_vector;

        const auto residual_dotted = Dot(residual_vector, residual_vector);
        const auto Ap = MatMult(A, p);
        const double alpha = residual_dotted / Dot(p, Ap);

        for (std::int32_t i = 0; i < n; ++i)
        {
            x.at(i) += alpha * p.at(i);
            residual_vector.at(i) -= alpha * Ap.at(i);
        }

        const auto new_residual_dotted = Dot(residual_vector, residual_vector);
        const auto beta = new_residual_dotted / residual_dotted;

        for (std::int32_t i = 0; i < n; ++i)
        {
            p.at(i) = residual_vector.at(i) + beta * p.at(i);
        }

        residual = L2Norm(residual_vector);
    }
        
}

}  // namespace matrix

}  // namespace nm
