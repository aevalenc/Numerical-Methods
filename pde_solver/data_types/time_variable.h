// Author: Alejandro Valencia
// CFD BU Online Course Step 2: 1D Nonlinear convection
// Update: 20 November, 2021

/*
 *
 */

#ifndef PDE_SOLVER_DATA_TYPES_TIME_VARIABLE_H
#define PDE_SOLVER_DATA_TYPES_TIME_VARIABLE_H

#include "pde_solver/data_types/spatial_variable.h"
#include <vector>

namespace pde
{

enum class TimeDiscretizationMethod
{
    kEulerStep = 0,
    kRungeKutta4,
    kRungeKutta2,
    kInvalid,
};

class TimeVariable
{
  public:
    TimeVariable() : time_discretization_method_{TimeDiscretizationMethod::kInvalid} {}
    TimeVariable(const SpatialVariable& u);

    ~TimeVariable() {}
    TimeVariable(const TimeVariable& other)
        : ux_(other.ux_),
          time_discretization_method_(other.time_discretization_method_),
          u_current_(other.u_current_),
          u_previous_(other.u_previous_),
          M_(other.M_),
          start_time_(other.start_time_),
          end_time_(other.end_time_),
          delta_t_(other.delta_t_)
    {
    }

    TimeVariable(TimeVariable&& other) noexcept
        : time_discretization_method_(other.time_discretization_method_),
          u_current_(other.u_current_),
          u_previous_(other.u_previous_) {};

    TimeVariable& operator=(const TimeVariable& other)
    {
        if (this != &other)
        {
            ux_ = other.ux_;
            time_discretization_method_ = other.time_discretization_method_;
            u_current_ = other.u_current_;
            u_previous_ = other.u_previous_;
            M_ = other.M_;
            start_time_ = other.start_time_;
            end_time_ = other.end_time_;
            delta_t_ = other.delta_t_;
        }

        return *this;
    }
    TimeVariable& operator=(TimeVariable&&) noexcept { return *this; }

  public:
    void SetTimeDiscretizationMethod(TimeDiscretizationMethod time_discretization_method);
    TimeDiscretizationMethod GetTimeDiscretizationMethod() const;
    void SetStartTime(const double start_time) { start_time_ = start_time; };
    void SetEndTime(const double end_time) { end_time_ = end_time; };
    void SetTimeStep(const double delta_t) { delta_t_ = delta_t; };
    void SetInitialCondition(const std::vector<double>& u_initial);
    void SetDirichletBoundaryCondition();
    void SetRightHandSideMatrix(const nm::matrix::Matrix<double>& rhs);
    void Step(const std::vector<double>& wave_speeds);
    void Run();
    void StepOnce();
    void GenerateMassMatrix();
    void InitializeWithSpatialVariable(const SpatialVariable& u);
    void Reset();
    SpatialVariable ux_{};

    std::vector<double>& GetTimeVariable() { return u_current_; }

  private:
    TimeDiscretizationMethod time_discretization_method_;
    std::vector<double> u_current_{};
    std::vector<double> u_previous_{};
    nm::matrix::Matrix<double> rhs_matrix_{};
    nm::matrix::Matrix<double> M_{};
    double start_time_{};
    double end_time_{};
    double delta_t_{};
};

}  // namespace pde

#endif  // PDE_SOLVER_DATA_TYPES_TIME_VARIABLE_H
