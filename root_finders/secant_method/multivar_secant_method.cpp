/*
 * Secant method implementation for finding roots of a continuous function.
 *
 * Author: Alejandro Valencia
 * Update: September 10th, 2025
 */

#include "root_finders/secant_method/multivar_secant_method.h"
#include "matrix_solvers/direct_solvers/lu_solve.h"
#include "matrix_solvers/operations/operations.h"
#include "matrix_solvers/utilities.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>

namespace nm
{
namespace root_finders
{
namespace
{
matrix::Matrix<double> EvaluateSystem(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                      std::vector<std::vector<double>>& equations_arguments)
{
    matrix::Matrix<double> A(equations.size() + 1, equations.size() + 1);
    std::int32_t i{};
    std::int32_t j{};
    for (auto& arguments : equations_arguments)
    {
        A.at(i).at(j) = 1;
        for (auto& equation : equations)
        {
            j++;
            const auto value = (equation(arguments));
            A.at(i).at(j) = value;
        }
        i++;
        j = 0;
    }
    const auto A_transposed = A.Transpose();
    return A_transposed;
}
}  // namespace

std::vector<double> MultiVarSecantMethod(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                         const std::vector<double>& x0,
                                         const std::vector<double>& x1,
                                         const std::vector<double>& x2,
                                         const double tolerance,
                                         const std::int32_t max_iterations)
{
    std::vector<double> xkm2{x0};
    std::vector<double> xkm1{x1};
    std::vector<double> xk{x2};
    std::vector<double> xkp1{};
    xkp1.resize(x0.size());

    std::vector<double> b{};
    b.resize(x0.size() + 1);
    b.at(0) = 1;

    for (std::int32_t k{1}; k < max_iterations; ++k)
    {
        std::vector<std::vector<double>> arguments = {xkm2, xkm1, xk};
        const auto A = EvaluateSystem(equations, arguments);
        const auto coefficients = matrix::LUSolve(A, b);

        for (std::int32_t i{0}; i < static_cast<std::int32_t>(arguments.size()); ++i)
        {
            const auto c = matrix::ScalarMultiply(coefficients.at(i), arguments.at(i));
            xkp1 = matrix::AddVectors(xkp1, c);
        }

        if (matrix::L2Norm(matrix::AddVectors(xkp1, matrix::ScalarMultiply(-1.0, xk))) < tolerance)
        {
            std::cout << "Secant method converged in " << k << " iterations.\n";
            break;
        }
        if (k == max_iterations - 1)
        {
            std::cout << "Max iterations reached.\n";
        }
        xkm2 = xkm1;
        xkm1 = xk;
        xk = xkp1;
        xkp1.assign(xkp1.size(), 0);
    }
    return xk;
}

}  // namespace root_finders
}  // namespace nm
