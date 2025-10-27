/*
 * Secant method for finding roots of a system of nonlinear equations.
 *
 * Author: Alejandro Valencia
 * Update: October 20th, 2025
 */

#ifndef ROOT_FINDERS_BROYDENS_METHOD_BROYDENS_METHOD_H
#define ROOT_FINDERS_BROYDENS_METHOD_BROYDENS_METHOD_H

#include "matrix_solvers/utilities.h"
#include <cstdint>
#include <functional>
#include <vector>

namespace nm
{
namespace root_finders
{

/**
 * @brief Evaluates the Jacobian matrix for a system of nonlinear equations.
 *
 * This function numerically approximates the Jacobian matrix for a given system of equations
 * using finite differences. The Jacobian is computed at the specified arguments for each equation.
 *
 * @param equations Vector of functions representing the system of equations. Each function takes a vector of doubles
 * and returns a double.
 * @param equations_arguments Arguments at which to evaluate the Jacobian, as a vector of vectors of doubles.
 * @param delta Perturbation value used for finite difference approximation.
 * @return matrix::Matrix<double> The approximated Jacobian matrix.
 */
matrix::Matrix<double> EvaluateJacobian(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                        const std::vector<double>& x,
                                        const double delta);

// matrix::Matrix<double> EstimateJacobianInverse(const std::vector<std::function<double(std::vector<double>)>>&
// equations,
//                                                const std::vector<double>& xk,
//                                                const std::vector<double>& F_x,
//                                                const std::vector<double>& xkp1,
//                                                const matrix::Matrix<double>& JacobianInverse);

/**
 * @brief Solves a system of nonlinear equations using Broyden's method (a quasi-Newton method).
 *
 * This function finds the roots of a system of nonlinear equations using Broyden's method, which is an efficient
 * iterative algorithm for solving multivariate nonlinear systems without requiring explicit Jacobian computation.
 *
 * @param equations Vector of functions representing the system of equations. Each function takes a vector of
 * doubles and returns a double.
 * @param equations_arguments Initial guesses for the variables, as a vector of vectors of doubles.
 * @param tolerance Convergence tolerance for the solution (default: 1e-6).
 * @param max_iterations Maximum number of iterations allowed (default: 1000).
 * @return std::vector<double> Solution vector containing the roots of the system.
 */
std::vector<double> BroydensMethod(const std::vector<std::function<double(std::vector<double>)>>& equations,
                                   const std::vector<double>& initial_guess,
                                   const double delta,
                                   const double tolerance = 1e-3,
                                   const std::int32_t max_iterations = 1000);

}  // namespace root_finders

}  // namespace nm

#endif  // ROOT_FINDERS_BROYDENS_METHOD_BROYDENS_METHOD_H
