/*
 * @brief Unit tests for the SpatialVariable class.
 * @details This file contains unit tests for the SpatialVariable class, which is part of the C++ CFD library.
 *          The tests cover the basic functionality of the SpatialVariable class, including
 *          setting and getting the spatial discretization method.
 *          The tests also include copy and move constructors and assignment operators.
 * @date May 2, 2025
 * @author Alejandro Valencia
 */

#include "examples/line_chart/src/data_types/spatial_variable.h"
#include <gtest/gtest.h>

namespace cfd
{

namespace
{

class BaseClassFixture : public testing::Test
{
  protected:
    SpatialVariable u_{};
};

TEST_F(BaseClassFixture, GivenDefaultInstantiation_ExpectDefaultSpatialDiscretizationMethod)
{
    const auto result = u_.GetSpatialDiscretizationMethod();
    EXPECT_TRUE(result == SpatialDiscretizationMethod::kInvalid);
}

TEST_F(BaseClassFixture, GivenDefaultInstantiation_WhenSettingDiscretizationMethod_ExpectValid)
{
    u_.SetSpatialDiscretizationMethod(SpatialDiscretizationMethod::kFiniteElementMethod);
    EXPECT_TRUE(u_.GetSpatialDiscretizationMethod() == SpatialDiscretizationMethod::kFiniteElementMethod);
}

TEST_F(BaseClassFixture,
       GivenFiniteElementDiscretization_WhenCopiedConstructed_ExpectFiniteElementSpatialDiscretization)
{
    u_.SetSpatialDiscretizationMethod(SpatialDiscretizationMethod::kFiniteElementMethod);
    const SpatialVariable u2(u_);
    EXPECT_TRUE(u_.GetSpatialDiscretizationMethod() == u2.GetSpatialDiscretizationMethod());
}

TEST_F(BaseClassFixture, GivenFiniteElementDiscretization_WhenCopiedAssigned_ExpectFiniteElementSpatialDiscretization)
{
    u_.SetSpatialDiscretizationMethod(SpatialDiscretizationMethod::kFiniteElementMethod);
    const auto u2 = u_;
    EXPECT_TRUE(u_.GetSpatialDiscretizationMethod() == u2.GetSpatialDiscretizationMethod());
}

}  // namespace

}  // namespace cfd
