/*
 * Author: Alejandro Valencia
 * Update: 16 April, 2023
 */

#include "matrix_solvers/iterative_solvers/jacobi.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <numeric>

namespace nm
{

namespace matrix
{

namespace
{

double L2Norm(const std::vector<double>& vector)
{
    std::vector<double> vector_squared{};

    std::transform(
        std::cbegin(vector), std::cend(vector), std::back_inserter(vector_squared), [](const auto& vector_element) {
            return vector_element * vector_element;
        });

    return std::sqrt(std::accumulate(std::cbegin(vector_squared), std::cend(vector_squared), 0.0));
}

}  // namespace

double jacobi(const std::vector<std::vector<double>>& A, const std::vector<double>& b, std::vector<double>& x)
{

    const auto x_initial = x;
    double sum{0.0};

    for (std::size_t i = 0; i < b.size(); ++i)
    {
        for (std::size_t j = 0; j < b.size(); ++j)
        {
            if (j != i)
            {
                sum += (A.at(i).at(j) * x.at(j));
            }
        }

        x.at(i) = (b.at(i) - sum) / A.at(i).at(i);
        sum = 0.0;
    }

    std::vector<double> residual{};
    std::transform(std::cbegin(x),
                   std::cend(x),
                   std::cbegin(x_initial),
                   std::back_inserter(residual),
                   [](const auto& x_element, const auto& x_initial_element) { return x_initial_element - x_element; });

    return L2Norm(residual);

}  // end FUNCTION jacobi

void jacobi(const std::vector<std::vector<double>>& A,
            const std::vector<double>& b,
            std::vector<double>& x,
            const int max_iterations,
            const double tolerance)
{
    auto x_new = x;
    auto residual_vector = x;
    double sum{0.0};
    double iteration{0.0};

    auto residual = std::numeric_limits<double>::infinity();

    while (residual > tolerance)
    {
        ++iteration;

        for (std::size_t i = 0; i < b.size(); ++i)
        {
            for (std::size_t j = 0; j < b.size(); ++j)
            {
                if (j != i)
                {
                    sum += (A.at(i).at(j) * x.at(j));
                }
            }

            x_new.at(i) = (b.at(i) - sum) / A.at(i).at(i);
            sum = 0.0;
        }

        std::transform(
            std::cbegin(x),
            std::cend(x),
            std::cbegin(x_new),
            std::back_inserter(residual_vector),
            [](const auto& x_element, const auto& x_initial_element) { return x_initial_element - x_element; });
        residual = L2Norm(residual_vector);

        if (iteration > max_iterations)
        {
            break;
        }
        else
        {
            x = x_new;
        }
    }

}  // end FUNCTION jacobi

}  // namespace matrix

}  // namespace nm
