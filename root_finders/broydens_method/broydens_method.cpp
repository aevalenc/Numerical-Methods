/*
 * Secant method implementation for finding roots of a continuous function.
 *
 * Author: Alejandro Valencia
 * Update: October 22nd, 2025
 */

#include "root_finders/broydens_method/broydens_method.h"
#include "matrix_solvers/operations/operations.h"
#include "matrix_solvers/utilities.h"
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace nm
{
namespace root_finders
{
namespace
{
matrix::Matrix<double> EvaluateSystem(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                      const std::vector<std::vector<double>>& equations_arguments)
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

std::pair<matrix::Matrix<double>, std::vector<double>> EvaluateJacobian(
    const std::vector<std::function<double(std::vector<double>)>>& equations,
    const std::vector<std::vector<double>>& equations_arguments,
    const double delta)
{
    const auto n = static_cast<std::int32_t>(equations.size());
    const auto I = matrix::CreateIdentityMatrix<double>(n);
    const auto H = matrix::ScalarMultiply(delta, I);

    matrix::Matrix<double> Jacobian(n, n);
    std::vector<double> xpdx{};
    std::vector<double> F_x{};
    std::vector<double> F_xpdx{};
    F_x.resize(n);
    F_xpdx.resize(n);
    for (std::int32_t i{0}; i < n; ++i)
    {
        xpdx = matrix::AddVectors(equations_arguments.at(0), matrix::MatMult(H, I.at(i)));
        for (std::int32_t j{0}; j < n; ++j)
        {
            F_x.at(j) = (equations.at(j)(equations_arguments.at(0)));
            F_xpdx.at(j) = (equations.at(j)(xpdx));
        }
        const auto dF = matrix::AddVectors(F_xpdx, matrix::ScalarMultiply(-1, F_x));
        Jacobian.at(i) = dF;
    }
    Jacobian = matrix::ScalarMultiply(1.0 / delta, Jacobian);
    return {Jacobian.Transpose(), F_x};
}

matrix::Matrix<double> EstimateJacobianInverse(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                               const std::vector<std::vector<double>>& equations_arguments,
                                               const double delta)
{
    const auto n = static_cast<std::int32_t>(equations.size());
    const auto I = matrix::CreateIdentityMatrix<double>(n);
    const auto H = matrix::ScalarMultiply(delta, I);

    matrix::Matrix<double> Jacobian(n, n);
    std::vector<double> xpdx{};
    std::vector<double> F_x{};
    std::vector<double> F_xpdx{};
    F_x.resize(n);
    F_xpdx.resize(n);
    for (std::int32_t i{0}; i < n; ++i)
    {
        xpdx = matrix::AddVectors(equations_arguments.at(0), matrix::MatMult(H, I.at(i)));
        for (std::int32_t j{0}; j < n; ++j)
        {
            F_x.at(j) = (equations.at(j)(equations_arguments.at(0)));
            F_xpdx.at(j) = (equations.at(j)(xpdx));
        }
        const auto dF = matrix::AddVectors(F_xpdx, matrix::ScalarMultiply(-1, F_x));
        Jacobian.at(i) = dF;
    }
    Jacobian = matrix::ScalarMultiply(1.0 / delta, Jacobian);
    return Jacobian.Transpose();
}

std::vector<double> BroydensMethod(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                   const std::vector<std::vector<double>>& equations_arguments,
                                   const double delta,
                                   const double tolerance,
                                   const std::int32_t max_iterations)
{

    std::vector<double> xk{equations_arguments.back()};
    std::vector<double> xkp1{};
    xkp1.resize(equations_arguments.at(0).size());

    const auto J = EvaluateJacobian(equations, equations_arguments, delta);
    const auto Jinverse = matrix::InvertWithLU(J);
    std::vector<double> Fxk{};
    for (std::int32_t k{1}; k < max_iterations; ++k)
    {
        for (auto& arguments : equations_arguments)
        {
            for (auto& equation : equations)
            {
                const auto value = (equation(arguments));
                Fxk.push_back(value);
            }
        }
        xkp1 = matrix::AddVectors(xk, matrix::MatMult(Jinverse, Fxk));

        if (matrix::L2Norm(matrix::AddVectors(xkp1, matrix::ScalarMultiply(-1.0, xk))) < tolerance)
        {
            std::cout << "Secant method converged in " << k << " iterations.\n";
            break;
        }
        if (k == max_iterations - 1)
        {
            std::cout << "Max iterations reached.\n";
        }

        xk = xkp1;
        xkp1.assign(xkp1.size(), 0);
    }
    return xk;
}

}  // namespace root_finders
}  // namespace nm
