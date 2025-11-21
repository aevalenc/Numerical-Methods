/*
 * Monte Carlo simulation for vacation budget planning.
 *
 * Author: Alejandro Valencia
 * Update: November 21, 2025
 *
 */

#include "matrix_solvers/utilities.h"
#include <array>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>

int main()
{
    const int num_simulations = static_cast<std::int32_t>(1e3);

    // Seed with a real random value, if available
    std::random_device r;
    std::default_random_engine generator(r());

    // Normal distribution for flight costs (mean = $1100, stddev = $300)
    const double flight_cost_mean = 1100.0;
    const double flight_cost_std_dev = 300.0;
    std::normal_distribution<double> flight_distribution(flight_cost_mean, flight_cost_std_dev);

    // Normal distribution for accommodation costs (mean = $1500, stddev = $400)
    const double accommodation_cost_mean = 500.0;
    const double accommodation_cost_std_dev = 120.0;
    std::normal_distribution<double> accommodation_distribution(accommodation_cost_mean, accommodation_cost_std_dev);

    // Uniform distribution for daily expenses (min = $50, max = $150)
    const double daily_expense_min = 50.0;
    const double daily_expense_max = 150.0;
    const double daily_expense_mean = (daily_expense_min + daily_expense_max) / 2.0;
    std::uniform_real_distribution<double> daily_expense_distribution(daily_expense_min, daily_expense_max);

    std::array<double, num_simulations> flight_costs{};
    std::array<double, num_simulations> accommodation_costs{};
    std::array<double, num_simulations> daily_expenses{};
    std::array<double, num_simulations> total_costs{};
    std::map<int, int> histogram{};
    for (int i = 0; i < num_simulations; ++i)
    {

        flight_costs.at(i) = flight_distribution(generator);
        accommodation_costs.at(i) = accommodation_distribution(generator);
        daily_expenses.at(i) = daily_expense_distribution(generator);

        const double single_run_cost = flight_costs.at(i) + accommodation_costs.at(i) + daily_expenses.at(i);
        total_costs.at(i) = single_run_cost;

#ifdef _DEBUG
        const int rounded_cost = static_cast<int>(std::round(single_run_cost));
        ++histogram[rounded_cost];
#endif
    }

    const double average_budget = std::accumulate(total_costs.begin(), total_costs.end(), 0.0) / total_costs.size();
    std::cout << "Estimated Average Vacation Budget: $" << average_budget << std::endl;

#ifdef _DEBUG
    for (auto [x, y] : histogram)
        std::cout << std::setw(2) << x << ' ' << std::string(y, '*') << '\n';
#endif

    // Calculate standard deviation
    double sum_squared_diff = 0.0;
    for (const auto& cost : total_costs)
    {
        sum_squared_diff += (cost - average_budget) * (cost - average_budget);
    }
    const double stddev_budget = std::sqrt(sum_squared_diff / total_costs.size());
    std::cout << "Estimated Standard Deviation of Vacation Budget: $" << stddev_budget << std::endl;

    // Calculate Covariance between flight, accommodation, and daily expenses
    nm::matrix::Matrix<double> expenses_matrix(num_simulations, 3);
    for (std::int32_t i = 0; i < num_simulations; ++i)
    {
        expenses_matrix.at(i).at(0) = flight_costs.at(i) - flight_cost_mean;
        expenses_matrix.at(i).at(1) = accommodation_costs.at(i) - accommodation_cost_mean;
        expenses_matrix.at(i).at(2) = daily_expenses.at(i) - daily_expense_mean;
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            double covariance = 0.0;
            for (int k = 0; k < num_simulations; ++k)
            {
                covariance += expenses_matrix.at(k).at(i) * expenses_matrix.at(k).at(j);
            }
            covariance /= num_simulations;
            std::cout << "Covariance between expense " << i << " and expense " << j << ": " << covariance << std::endl;
        }
    }

    return 0;
}
