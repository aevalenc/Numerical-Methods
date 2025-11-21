"""
Monte Carlo simulation for vacation budget planning.
"""

import random

import matplotlib.pyplot as plt
import numpy as np


def uniform():

    rng_generator = np.random.default_rng(seed=10)

    number_of_samples = 1000

    flight_cost_min = 500
    flight_cost_max = 1000
    flight_cost_samples = rng_generator.uniform(flight_cost_min, flight_cost_max, number_of_samples)

    hotel_nightly_cost_min = 80
    hotel_nightly_cost_max = 200
    hotel_nightly_cost_samples = rng_generator.uniform(
        hotel_nightly_cost_min, hotel_nightly_cost_max, number_of_samples
    )

    total_cost_dist = flight_cost_samples + (hotel_nightly_cost_samples * 3)

    # using tuple unpacking for multiple Axes
    fig, (ax1, ax2) = plt.subplots(1, 2)
    ax1.set_title("Density Distribution")
    ax1.hist(total_cost_dist, density=True)
    ax2.set_title("Cumulative Distribution")
    ax2.hist(total_cost_dist, cumulative=True, density=True)

    print(f"Mean total cost (uniform): {np.mean(total_cost_dist)}")


def normal():
    rng_generator = np.random.default_rng(seed=10)
    number_of_samples = 1000

    flight_cost_mean = 750
    flight_cost_stddev = 100
    flight_cost_samples = rng_generator.normal(flight_cost_mean, flight_cost_stddev, number_of_samples)
    hotel_nightly_cost_mean = 140
    hotel_nightly_cost_stddev = 40
    hotel_nightly_cost_samples = rng_generator.normal(
        hotel_nightly_cost_mean, hotel_nightly_cost_stddev, number_of_samples
    )
    total_cost_dist = flight_cost_samples + (hotel_nightly_cost_samples * 3)
    print(f"Mean total cost (normal): {np.mean(total_cost_dist)}")

    fig, (ax1, ax2) = plt.subplots(1, 2)
    ax1.set_title("Density Normal Distributions")
    ax1.hist(total_cost_dist, density=True)
    ax2.set_title("Cumulative Normal Distributions")
    ax2.hist(total_cost_dist, cumulative=True, density=True)


if __name__ == "__main__":
    print("Running Monte Carlo simulation for vacation budget planning")
    uniform()
    normal()
    plt.show()
