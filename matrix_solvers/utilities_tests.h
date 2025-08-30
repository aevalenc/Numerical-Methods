/*
 * Matrix utilities tests
 *
 * Author: Alejandro Valencia
 * Update: August 27, 2025
 */

#ifndef MATRIX_SOLVERS_UTILITIES_TESTS_H
#define MATRIX_SOLVERS_UTILITIES_TESTS_H

#include "matrix_solvers/utilities.h"
#include <gtest/gtest.h>
#include <vector>

namespace nm
{

namespace matrix
{

namespace test
{

class MatrixUtilitiesBaseTestFixture : public ::testing::Test
{
  public:
    void SetUp() override
    {
        A_.push_back(std::vector<double>{1.0, 0.0, 1.0});
        A_.push_back(std::vector<double>{2.0, 1.0, 1.0});
        A_.push_back(std::vector<double>{0.0, 1.0, 1.0});
        A_.push_back(std::vector<double>{1.0, 1.0, 2.0});

        B_.push_back(std::vector<double>{1.0, 2.0, 1.0});
        B_.push_back(std::vector<double>{2.0, 3.0, 1.0});
        B_.push_back(std::vector<double>{4.0, 2.0, 2.0});

        C_.push_back(std::vector<double>{5.0, 4.0, 3.0});
        C_.push_back(std::vector<double>{8.0, 9.0, 5.0});
        C_.push_back(std::vector<double>{6.0, 5.0, 3.0});
        C_.push_back(std::vector<double>{11.0, 9.0, 6.0});
    }

  public:
    Matrix<double> A_{};
    Matrix<double> B_{};
    Matrix<double> C_{};
    double tolerance_{0.001};
};

}  // namespace test

}  // namespace matrix

}  // namespace nm

#endif  // MATRIX_SOLVERS_UTILITIES_TESTS_H
