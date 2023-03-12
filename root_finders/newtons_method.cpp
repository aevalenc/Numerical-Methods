/*
 * Author : Alejandro Valencia
 * Project: Newton's Method
 * Update : 11 June, 2022
 */

#include "root_finders/newtons_method.h"
#include <iostream>

namespace nm
{

namespace polysolver
{

double NewtonsMethod(double &x_0)
{
  const auto tol = std::numeric_limits<double>::epsilon();
  std::size_t itrmx = 1000;
  double x_n{};

  for (std::size_t i = 0; i < itrmx; i++)
  {
    x_n = x_0 - f(x_0) / fprime(x_0);

    if (std::abs(x_n - x_0) < tol)
    {
      break;
    }
    x_0 = x_n;
  }

  return x_n;
}

} // namespace polysolver

} // namespace nm
