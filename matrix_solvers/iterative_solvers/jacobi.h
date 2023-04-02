/*
 * Author: ALejandro Valencia
 * Update: 12 March, 2023
 */

#include <vector>

namespace nm
{

namespace matrix
{

/// @brief This function implements the jacobi method
///
/// @param A: nxn Matrix
/// @param x: Initialized solution
/// @param b:	Right hand side of matrix equation
///
/// @return res: 	Max absolute error defined max(|x-x0|)
double jacobi(const std::vector<std::vector<double>> &A,
              const std::vector<double> &b, std::vector<double> &x);

/// @brief This function implements the jacobi method
///
/// @param A: nxn Matrix
/// @param x0: Initial guess to solution
/// @param b:	Right hand side of matrix equation
/// @param x:	Next iteration of the solution
///
/// @return res: 	Max absolute error defined max(|x-x0|)
double jacobi(double A[], double x0[], double b[], int n, double x[]);

} // namespace matrix

} // namespace nm
