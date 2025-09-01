/*
 * Newton Kleinman Method to solve the LQR problem for control systems
 *
 * Author: Alejandro Valencia
 * Update: September 1st
 */

#ifndef CONTROLS_LQR_NEWTON_KLEINMAN_H
#define CONTROLS_LQR_NEWTON_KLEINMAN_H

#include "matrix_solvers/utilities.h"

namespace nm
{
namespace controls
{

nm::matrix::Matrix<double> NewtonKleinman(const nm::matrix::Matrix<double>& A,
                                          const nm::matrix::Matrix<double>& B,
                                          const nm::matrix::Matrix<double>& Q,
                                          const nm::matrix::Matrix<double>& R,
                                          const nm::matrix::Matrix<double>& K0);

}  // namespace controls
}  // namespace nm

#endif  // CONTROLS_LQR_NEWTON_KLEINMAN_H
