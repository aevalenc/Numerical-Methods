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
std::vector<double> EvaluateSystem(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                   const std::vector<std::vector<double>>& equations_arguments)
{
    std::vector<double> Fx{};
    for (auto& arguments : equations_arguments)
    {
        for (auto& equation : equations)
        {
            const auto value = (equation(arguments));
            Fx.push_back(value);
        }
    }
    return Fx;
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
                                               const std::vector<double>& F_x,
                                               const std::vector<double>& xkp1,
                                               const matrix::Matrix<double>& JacobianInverse)
{
    const auto n = static_cast<std::int32_t>(equations.size());
    const auto I = matrix::CreateIdentityMatrix<double>(n);

    matrix::Matrix<double> JInverse_kp1(n, n);

    std::vector<double> F_xkp1{};
    F_xkp1.resize(n);
    F_xkp1 = EvaluateSystem(equations, {xkp1});

    const auto delta_x = matrix::AddVectors(xkp1, equations_arguments.back());
    const auto delta_F = matrix::AddVectors(F_xkp1, F_x);

    const matrix::Matrix<double> numerator{
        {matrix::AddVectors(delta_x, matrix::ScalarMultiply(-1, matrix::MatMult(JacobianInverse, delta_F)))}};

    matrix::Matrix<double> delta_x_as_matrix{{delta_x}};
    matrix::Matrix<double> delta_F_as_matrix{{delta_F}};
    const auto delta_x_J_inv = matrix::MatMult(delta_x_as_matrix, JacobianInverse);
    const auto denominator = matrix::MatMult(delta_x_J_inv, delta_F_as_matrix.Transpose());
    const auto coefficient = matrix::ScalarMultiply(1 / denominator.back().back(), numerator);

    const auto delta_Jinverse =
        matrix::MatMult(matrix::MatMult(coefficient.Transpose(), delta_x_as_matrix), JacobianInverse);

    JInverse_kp1 = JacobianInverse + delta_Jinverse;
    return JInverse_kp1;
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

    const auto J_Fx_pair = EvaluateJacobian(equations, equations_arguments, delta);
    auto Jinverse = matrix::InvertWithLU(J_Fx_pair.first);
    std::vector<double> Fxk{};
    double residual{};
    for (std::int32_t k{1}; k < max_iterations; ++k)
    {

        xkp1 = matrix::AddVectors(
            xk, matrix::ScalarMultiply(-1, matrix::MatMult(Jinverse, EvaluateSystem(equations, equations_arguments))));

        const auto delta_x = matrix::AddVectors(xkp1, matrix::ScalarMultiply(-1.0, xk));
        residual = matrix::L2Norm(delta_x);
        if (residual < tolerance)
        {
            std::cout << "Secant method converged in " << k << " iterations.\n";
            break;
        }
        if (k == max_iterations - 1)
        {
            std::cout << "Max iterations reached. Residual: " << residual << "\n";
        }

        Jinverse = EstimateJacobianInverse(
            equations, equations_arguments, EvaluateSystem(equations, equations_arguments), xkp1, Jinverse);
        xk = xkp1;
    }
    return xkp1;
}

}  // namespace root_finders
}  // namespace nm
