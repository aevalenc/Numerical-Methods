/*
 * Main computation file
 *
 * Author: Alejandro Valencia
 * Update: August 19th, 2025
 *
 */

#ifndef PDE_SOLVER_MAIN_SOLVER_H
#define PDE_SOLVER_MAIN_SOLVER_H

#include "pde_solver/data_types/time_variable.h"

class Solver
{

  public:
    void SetupLinearAdvection();
    void CallStepOnce();
    pde::TimeVariable uu{};
    std::vector<double> x_;

    double delta_t_{0.1};
    double end_time_{0.5};
    double current_time_{0.0};

  public:
    Solver(const double delta_t, const double end_time);
};

#endif
