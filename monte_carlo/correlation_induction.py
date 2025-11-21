"""
Monte Carlo simulation for vacation budget planning.
"""

import random

import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import beta
import pandas as pd


def pert_sampling(min_value, most_likely, max_value, rng_generator, num_samples=1000, lambda_factor=4):
    """
    Perform PERT sampling given min, most likely, and max values.
    """

    # Calculate alpha and beta parameters for the beta distribution
    alpha = 1 + lambda_factor * ((most_likely - min_value) / (max_value - min_value))
    beta_param = 1 + lambda_factor * ((max_value - most_likely) / (max_value - min_value))

    # Generate samples from the beta distribution
    beta_samples = beta.rvs(alpha, beta_param, size=num_samples, random_state=rng_generator)

    # Scale samples to the desired range
    scaled_samples = min_value + beta_samples * (max_value - min_value)

    return scaled_samples


def main():
    rng_generator = np.random.default_rng(seed=10)
    number_of_samples = 10000

    # generate samples
    flight_costs = pert_sampling(500.0, 800.0, 1200.0, rng_generator, num_samples=number_of_samples)
    accommodation_costs = pert_sampling(600.0, 900.0, 1500.0, rng_generator, num_samples=number_of_samples)
    food_costs = pert_sampling(300.0, 500.0, 800.0, rng_generator, num_samples=number_of_samples)
    activity_costs = rng_generator.uniform(200.0, 600.0, number_of_samples)

    total_costs = flight_costs + accommodation_costs + food_costs + activity_costs

    # using tuple unpacking for multiple Axes
    fig, (ax1, ax2) = plt.subplots(1, 2)
    ax1.set_title("Density Distribution")
    ax1.hist(total_costs, density=True, bins=100)
    ax2.set_title("Cumulative Distribution")
    ax2.hist(total_costs, cumulative=True, density=True, bins=100)

    print(f"Mean: {np.mean(total_costs)}")
    print(f"Min: {np.min(total_costs)}")
    print(f"Max: {np.max(total_costs)}")

    data = np.vstack((flight_costs, accommodation_costs, food_costs, activity_costs, total_costs))
    column_names = ["Flight Costs", "Accommodation Costs", "Food Costs", "Activity Costs", "Total Costs"]
    df = pd.DataFrame(data.T, columns=column_names)
    print(df)
    print(df.describe())

    correlation_matrix = df.corr()
    print(f"Correlation Matrix: {correlation_matrix}")

    figure_2, (ax3, ax4) = plt.subplots(1, 2, figsize=(10, 4))
    im1 = ax3.imshow(correlation_matrix, cmap="coolwarm", vmin=-1, vmax=1)
    figure_2.colorbar(im1, ax=ax3, label="Correlation")
    ax3.set_xticks(range(len(correlation_matrix)))
    ax3.set_xticklabels(correlation_matrix.columns, rotation=45)
    ax3.set_yticks(range(len(correlation_matrix)))
    ax3.set_yticklabels(correlation_matrix.columns)
    ax3.set_title("Correlation Heatmap")

    applied_correlation = np.array(
        [
            [1.00, 0, 0.85, 0.5, 0.2],
            [0, 1.00, 0.85, 0.5, 0.2],
            [0.85, 0.85, 1.0, 0.5, 0.2],
            [0.5, 0.5, 0.5, 1.0, 0.2],
            [0.2, 0.2, 0.2, 0.2, 1.0],
        ]
    )

    im2 = ax4.imshow(applied_correlation, cmap="coolwarm", vmin=-1, vmax=1)
    figure_2.colorbar(im2, ax=ax4, label="Correlation")
    labels = correlation_matrix.columns
    ax4.set_xticks(range(len(applied_correlation)))
    ax4.set_xticklabels(labels, rotation=45)
    ax4.set_yticks(range(len(applied_correlation)))
    ax4.set_yticklabels(labels)
    ax4.set_title("Applied Correlation")

    figure_2.tight_layout()


if __name__ == "__main__":
    print("Running Monte Carlo simulation for vacation budget planning")
    main()
    plt.show()
