/*
 * Author: Alejandro Valencia
 * Update: October 8, 2023
 */

#include "matrix_solvers/iterative_solvers/gauss_seidel.h"
#include "matrix_solvers/utilities.h"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>

namespace nm
{

namespace matrix
{

namespace
{

std::vector<double> CalculateResidual(const Matrix<double>& A,
                                      const std::vector<double>& b,
                                      const std::vector<double>& x,
                                      const std::int32_t n)
{
    std::vector<double> residual{};
    residual.resize(n);
    const auto Ax = MatMult(A, x);
    for (std::int32_t i = 0; i < n; ++i)
    {
        residual.push_back(b.at(i) - Ax.at(i));
    }
    return residual;
}

}  // namespace

std::pair<std::vector<double>, std::vector<double>> ConjugateGradient(const Matrix<double>& A,
                                                                      const std::vector<double>& b,
                                                                      std::vector<double>& x)
{

    const auto n = static_cast<std::int32_t>(b.size());

    auto residual = CalculateResidual(A, b, x, n);
    auto p(residual);

    const auto Ap = MatMult(A, p);
    const auto residual_dotted = Dot(residual, residual);
    const double alpha = residual_dotted / Dot(p, Ap);

    for (std::int32_t i = 0; i < n; ++i)
    {
        x.at(i) += alpha * p.at(i);
        residual.at(i) -= alpha * Ap.at(i);
    }

    const auto new_residual_dotted = Dot(residual, residual);
    const auto beta = new_residual_dotted / residual_dotted;

    for (std::int32_t i = 0; i < n; ++i)
    {
        p.at(i) = residual.at(i) + beta * p.at(i);
    }

    return std::make_pair(residual, p);
}

void GaussSeidel(const std::vector<std::vector<double>>& A,
                 const std::vector<double>& b,
                 std::vector<double>& x,
                 const int max_iterations,
                 const double tolerance)
{
    const auto x_initial = x;
    auto residual_vector = x;
    double sum{0.0};
    double iteration{0.0};

    auto residual = std::numeric_limits<double>::infinity();

    while (residual > tolerance)
    {
        ++iteration;

        for (std::int32_t i = 0; i < static_cast<std::int32_t>(b.size()); ++i)
        {
            for (std::int32_t j = 0; j < static_cast<std::int32_t>(b.size()); ++j)
            {
                if (j != i)
                {
                    sum += (A.at(i).at(j) * x.at(j));
                }
            }

            x.at(i) = (b.at(i) - sum) / A.at(i).at(i);
            sum = 0.0;
        }

        std::ignore = std::transform(
            std::cbegin(x),
            std::cend(x),
            std::cbegin(x_initial),
            std::back_inserter(residual_vector),
            [](const auto& x_element, const auto& x_initial_element) { return x_initial_element - x_element; });
        residual = L2Norm(residual_vector);

        if (iteration > max_iterations)
        {
            break;
        }
    }
}

}  // namespace matrix

}  // namespace nm
