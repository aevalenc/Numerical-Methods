/*
 * Author: Alejandro Valencia
 * Update: March, 9 2025
 */

#ifndef CALCULUS_DATA_TYPES_DATA_TYPES_H
#define CALCULUS_DATA_TYPES_DATA_TYPES_H

namespace nm
{
namespace calculus
{

class DualNumber
{
  public:
    double real{0.0};
    double dual{0.0};
    DualNumber() = default;
    DualNumber(double real, double dual) : real(real), dual(dual) {}
    DualNumber operator+(const DualNumber& other) const { return DualNumber(real + other.real, dual + other.dual); }
    DualNumber operator-(const DualNumber& other) const { return DualNumber(real - other.real, dual - other.dual); }
    DualNumber operator*(const DualNumber& other) const
    {
        return DualNumber(real * other.real, real * other.dual + dual * other.real);
    }
    DualNumber operator/(const DualNumber& other) const
    {
        return DualNumber(real / other.real, (dual * other.real - real * other.dual) / (other.real * other.real));
    }
};

}  // namespace calculus
}  // namespace nm

#endif  // CALCULUS_DATA_TYPES_DATA_TYPES_H