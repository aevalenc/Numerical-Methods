/*
 * Main computation file
 *
 * Author: Alejandro Valencia
 * Update: August 19th, 2025
 *
 */

#include "pde_solver/data_types/time_variable.h"

class Solver
{

  public:
    void SetupLinearAdvection();
    void CallStepOnce();
    cfd::TimeVariable uu{};
    std::vector<double> x_;

    double delta_t_{0.1};
    double end_time_{0.5};
    double current_time_{0.0};

  public:
    Solver(const double delta_t, const double end_time);
};
