// Author: Alejandro Valencia
// CFD BU Online Course Step 2: 1D Nonlinear convection
// Update: 20 November, 2021

/*
 *
 */

#ifndef PDE_SOLVER_DATA_TYPES_SPATIAL_VARIABLE_H
#define PDE_SOLVER_DATA_TYPES_SPATIAL_VARIABLE_H

#include "matrix_solvers/utilities.h"
#include "pde_solver/data_types/discretization_methods.h"
#include "pde_solver/data_types/finite_difference_schemas.h"
#include "pde_solver/data_types/grid.h"
#include <vector>

namespace pde
{

// Should be in Numerical Methods
enum class MatrixSolverEnum : std::int16_t
{
    kJacobi = 0,
    kGaussSeidel = 1,
    kConjugateGradient = 2,
    kLUSolve = 3,
    kInvalid = 255,
};

inline MatrixSolverEnum MatrixSolverEnumFromString(const std::string& str)
{
    if (str == "Jacobi")
    {
        return MatrixSolverEnum::kJacobi;
    }
    if (str == "GaussSeidel")
    {
        return MatrixSolverEnum::kGaussSeidel;
    }
    if (str == "ConjugateGradient")
    {
        return MatrixSolverEnum::kConjugateGradient;
    }
    if (str == "LUSolve")
    {
        return MatrixSolverEnum::kLUSolve;
    }
    return MatrixSolverEnum::kInvalid;
};

inline std::string MatrixSolverEnumToString(const MatrixSolverEnum method)
{
    switch (method)
    {
        case MatrixSolverEnum::kJacobi:
            return "Jacobi";
        case MatrixSolverEnum::kGaussSeidel:
            return "GaussSeidel";
        case MatrixSolverEnum::kConjugateGradient:
            return "ConjugateGradient";
        case MatrixSolverEnum::kLUSolve:
            return "LUSolve";
        default:
            return "Invalid";
    }
}

class SpatialVariable
{
  public:
    SpatialVariable() : spatial_discretization_method_{SpatialDiscretizationMethod::kInvalid} {}

    ~SpatialVariable() {}
    SpatialVariable(const SpatialVariable& other)
        : spatial_discretization_method_(other.spatial_discretization_method_),
          discretization_schema_(other.discretization_schema_),
          discretized_variable_(other.discretized_variable_),
          K_(other.K_),
          C_(other.C_),
          f_(other.f_),
          matrix_solver_(other.matrix_solver_),
          spatial_grid_(other.spatial_grid_) {};
    SpatialVariable(SpatialVariable&& other) noexcept
        : spatial_discretization_method_(std::move(other.spatial_discretization_method_)),
          discretization_schema_(std::move(other.discretization_schema_)),
          discretized_variable_(std::move(other.discretized_variable_)),
          K_(std::move(other.K_)),
          C_(std::move(other.C_)),
          f_(std::move(other.f_)),
          matrix_solver_(std::move(other.matrix_solver_)),
          spatial_grid_(std::move(other.spatial_grid_)) {};
    SpatialVariable& operator=(const SpatialVariable& other)
    {
        if (this != &other)
        {
            spatial_discretization_method_ = other.spatial_discretization_method_;
            discretization_schema_ = other.discretization_schema_;
            discretized_variable_ = other.discretized_variable_;
            K_ = other.K_;
            C_ = other.C_;
            f_ = other.f_;
            matrix_solver_ = other.matrix_solver_;
            spatial_grid_ = other.spatial_grid_;
        }
        return *this;
    }
    SpatialVariable& operator=(SpatialVariable&& other) noexcept
    {
        if (this != &other)
        {
            spatial_discretization_method_ = std::move(other.spatial_discretization_method_);
            discretization_schema_ = std::move(other.discretization_schema_);
            discretized_variable_ = std::move(other.discretized_variable_);
            K_ = std::move(other.K_);
            C_ = std::move(other.C_);
            f_ = std::move(other.f_);
            matrix_solver_ = std::move(other.matrix_solver_);
            spatial_grid_ = std::move(other.spatial_grid_);
        }
        return *this;
    }

  public:
    void SetSpatialDiscretizationMethod(SpatialDiscretizationMethod spatial_discretization_method);
    SpatialDiscretizationMethod GetSpatialDiscretizationMethod() const;

    void SetDiscretizationSchema(FiniteDifferenceSchema discretization_schema);
    FiniteDifferenceSchema GetDiscretizationSchema() const { return discretization_schema_; };

    const std::vector<double>& GetDiscretizedVariable() const { return discretized_variable_; };

    void SetGrid(const pde::geometry::Grid& grid);
    geometry::Grid GetGrid() const;

    void SetDirichletBoundaryCondition(const double value, const std::string_view& boundary_name);
    void SetDirichletBoundaryCondition(const double value, const std::int32_t boundary_index);

    void SetStiffnessMatrix(nm::matrix::Matrix<double> K);
    void SetDampingMatrix(nm::matrix::Matrix<double> C);
    void SetForceVector(std::vector<double> f);

    nm::matrix::Matrix<double> GetStiffnessMatrix() const { return K_; }
    nm::matrix::Matrix<double> GetDampingMatrix() const { return C_; }
    std::vector<double> GetForceVector() const { return f_; };

    void SetMatrixSolver(const MatrixSolverEnum matrix_solver);

    void Solve(const std::int32_t max_iterations, const double tolerance);

  private:
    SpatialDiscretizationMethod spatial_discretization_method_{};
    FiniteDifferenceSchema discretization_schema_{};
    std::vector<double> discretized_variable_{};
    nm::matrix::Matrix<double> K_{};
    nm::matrix::Matrix<double> C_{};
    std::vector<double> f_{};
    MatrixSolverEnum matrix_solver_{MatrixSolverEnum::kInvalid};
    geometry::Grid spatial_grid_{};
};

}  // namespace pde

#endif  // PDE_SOLVER_DATA_TYPES_SPATIAL_VARIABLE_H
