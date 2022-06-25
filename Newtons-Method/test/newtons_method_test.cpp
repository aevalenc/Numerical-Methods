/*
 * Author : Alejandro Valencia
 * Project: Newton's Method - main unit tests
*/

#include "Newtons-Method/src/newtons_method.h"
#include <gtest/gtest.h>
#include <cmath>

namespace
{

  class NewtonsMethodTestBaseFixture : public ::testing::Test
  {
  public:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    NewtonsMethodTestBaseFixture()
    {
      // You can do set-up work for each test here.
    }

    ~NewtonsMethodTestBaseFixture()
    {
      // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Class members declared here can be used by all tests in the test suite
    // for Foo.
  };

  class NewtonsMethodTest : public NewtonsMethodTestBaseFixture
  {
  };

  TEST(NewtonsMethodTest, GivenInitialGuessCloserToFirstRoot_ExpectFirstRootFound)
  {
    double x_0 = 0.25;
    const auto result = NewtonsMethod(x_0);
    EXPECT_NEAR(result, 0.0, std::numeric_limits<double>::epsilon());
  }

  TEST(NewtonsMethodTest, GivenInitialGuessCloserToSecondRoot_ExpectSecondRootFound)
  {
    double x_0 = 0.75;
    const auto result = NewtonsMethod(x_0);
    EXPECT_NEAR(result, 1.0, std::numeric_limits<double>::epsilon());
  }

  TEST(NewtonsMethodTest, GivenInitialGuessAtLocalMaxima_ExpectNaN)
  {
    double x_0 = 0.5;
    const auto result = NewtonsMethod(x_0);
    EXPECT_TRUE(std::isnan(result));
  }

} // namespace
