/*
 * Author: Alejandro Valencia
 * 12-Steps-To-NS: Gradient Operator
 * Update: April 13, 2024
 */

#ifndef PDE_SOLVER_OPERATORS_GRADIENT_H
#define PDE_SOLVER_OPERATORS_GRADIENT_H

#include "matrix_solvers/utilities.h"
#include "pde_solver/data_types/spatial_variable.h"
#include <cstdint>

namespace pde
{

namespace operators
{

class GradientOperator
{
  public:
    const nm::matrix::Matrix<double> GenerateMatrix();
    void GenerateMatrixForSpatialVariable(SpatialVariable& u);
    void SetSpatialVariable(const SpatialVariable& u_in);
    void SetWaveSpeed(const double wave_speed);

  public:
    GradientOperator() {};
    explicit GradientOperator(const double wave_speed);
    ~GradientOperator() = default;

    GradientOperator(const GradientOperator& other)
        : u_(other.u_), dimension_(other.dimension_), matrix_size_(other.matrix_size_), wave_speed_(other.wave_speed_)
    {
    }
    GradientOperator& operator=(const GradientOperator& other)
    {
        if (this != &other)
        {
            u_ = other.u_;
            dimension_ = other.dimension_;
            matrix_size_ = other.matrix_size_;
            wave_speed_ = other.wave_speed_;
        }
        return *this;
    }

    GradientOperator& operator=(GradientOperator&& other) noexcept
    {
        if (this != &other)
        {
            u_ = other.u_;
            dimension_ = other.dimension_;
            matrix_size_ = other.matrix_size_;
            wave_speed_ = other.wave_speed_;

            other.u_ = nullptr;
            other.dimension_ = 0;
            other.matrix_size_ = 0;
            other.wave_speed_ = 0.0;
        }
        return *this;
    }
    GradientOperator(GradientOperator&& other) noexcept
        : u_(other.u_), dimension_(other.dimension_), matrix_size_(other.matrix_size_), wave_speed_(other.wave_speed_)
    {
        other.u_ = nullptr;
        other.dimension_ = 0;
        other.matrix_size_ = 0;
        other.wave_speed_ = 0.0;
    }

  private:
    const SpatialVariable* u_{};
    std::int8_t dimension_{1};
    std::int32_t matrix_size_{};
    double wave_speed_{};
};

}  // namespace operators

}  // namespace pde

#endif  // PDE_SOLVER_OPERATORS_GRADIENT_H
