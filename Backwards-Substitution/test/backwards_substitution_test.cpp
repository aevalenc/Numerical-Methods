/*
 * Author : Alejandro Valencia
 * Project: Backwards Substitution - main unit tests
 */

#include "Backwards-Substitution/src/backwards_substitution.h"
#include <gtest/gtest.h>
namespace nm {
namespace matrix {
namespace {

class BackwardsSubstitutionTestBaseFixture : public ::testing::Test {
public:
  // You can remove any or all of the following functions if their bodies would
  // be empty.

  BackwardsSubstitutionTestBaseFixture() {
    // You can do set-up work for each test here.
  }

  ~BackwardsSubstitutionTestBaseFixture() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  // Class members declared here can be used by all tests in the test suite
  // for Foo.
};

class BackwardsSubstitutionTest : public BackwardsSubstitutionTestBaseFixture {
};

TEST(BackwardsSubstitutionTest,
     GivenUpperTriangularMatrix_ExpectExactSolution) {
  std::vector<std::vector<double>> A;
  A[0][0] = 1;
  A[0][1] = 0;
  A[1][0] = 0;
  A[1][1] = 1;
  std::vector<double> b;
  b.push_back(3);
  b.push_back(4);
  std::vector<double> x{0, 0};
  BackwardsSubstitution(A, x, b);
  EXPECT_EQ(x[0], b[0]);
  EXPECT_EQ(x[1], b[1]);
}

} // namespace
} // namespace matrix
} // namespace nm